/*
  Copyright 2016 Ryuichi Creative

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "countly/Network.h"
#include "countly/Version.h"

#include <cstring>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <errno.h>

namespace countly
{

Network::Network()
{
  // https://wiki.openssl.org/index.php/Library_Initialization
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  ERR_load_crypto_strings();
}

Network::~Network()
{
  FIPS_mode_set(0);
  EVP_cleanup();
  CRYPTO_cleanup_all_ex_data();
  ERR_free_strings();
}

std::string Network::urlencode(const std::string &unescaped)
{
  // http://stackoverflow.com/a/17708801
  std::ostringstream escaped;
  escaped.fill('0');
  escaped << std::hex;

  for (std::string::const_iterator i = unescaped.begin(), n = unescaped.end();
       i != n;
       i++)
  {
    std::string::value_type c = (*i); //!OCLINT

    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
    {
      escaped << c;
      continue;
    }

    escaped << '%' << std::setw(2) << int((unsigned char)c);
  }

  return escaped.str();
}

bool Network::get(std::string host, std::string query)
{
  int socket = _httpsConnect(host);
  if (socket < 0)
  {
    return false;
  }

  std::stringstream http;
  http << "GET " << query << " HTTP/1.0\r\n";
  http << "Host: " << _getIp(host) << "\r\n";
  http << "Connection: Close\r\n";
  http << "User-Agent: " << Version::toUserAgent() << " \r\n\r\n";

  bool success = _send((char *)http.str().c_str(), http.str().size());
  if (!success)
  {
    _httpsClose(socket);
    return false;
  }

  char buffer[512];
  memset(buffer, 0x00, 512);
  int size = SSL_read(_sslConnection, (char *)buffer, 512);
  success = (size >= 15) && (!memcmp(buffer, "HTTP/1.1 200 OK", 15));
  _httpsClose(socket);
  return success;
}

int Network::_httpConnect(std::string host)
{
  int sckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in scktAddr;
  memset((char *) &scktAddr, 0x00, sizeof(scktAddr));
  scktAddr.sin_family = AF_INET;
  scktAddr.sin_addr.s_addr = inet_addr((char *)_getIp(host).c_str());
  scktAddr.sin_port = htons(443); //!OCLINT

  int result = connect(sckt, (struct sockaddr *)&scktAddr, sizeof(scktAddr));
  if (result < 0 && errno != EISCONN)
  {
    return -1;
  }

  return sckt;
}

void Network::_httpClose(int socket)
{
  close(socket);
}

int Network::_httpsConnect(std::string host)
{
  int socket = _httpConnect(host);
  if (socket < 0)
  {
    return socket;
  }

  SSL_CTX *sslContext = SSL_CTX_new(SSLv23_client_method());
  _sslConnection = SSL_new(sslContext);
  SSL_set_fd(_sslConnection, socket);

  int err = SSL_connect(_sslConnection);
  if (err <= 0)
  {
    SSL_shutdown(_sslConnection);
    SSL_free(_sslConnection);
    return -1;
  }
  return socket;
}

void Network::_httpsClose(int socket)
{
  SSL_shutdown(_sslConnection);
  SSL_free(_sslConnection);
  _httpClose(socket);
}

bool Network::_send(char * buffer, int size)
{
  return SSL_write(_sslConnection, buffer, size) > 0;
}

std::string Network::_getIp(std::string host)
{
  struct hostent *ent = gethostbyname(host.c_str());

  if (ent && ent->h_addr_list && ent->h_addr_list[0] && ent->h_length == 4)
  {
    std::stringstream ip; //!OCLINT
    for (size_t i = 0; i < 4; i++) {
      if (i != 0) {
        ip << ".";
      }
      int node = (int)ent->h_addr_list[0][i];
      if (node < 0) {
        node += 256;
      }
      ip << node;
    }
    return ip.str();
  }
  // TODO: ipv6 support;

  return "";
}

} // end namespace countly
