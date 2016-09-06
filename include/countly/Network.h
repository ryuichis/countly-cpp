/*
  Copyright 2016 Ryuichi Saito, LLC

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

#ifndef COUNTLY_NETWORK_H
#define COUNTLY_NETWORK_H

#include <string>
#include <openssl/ssl.h>

namespace countly
{

class Network
{
private:
  SSL * _sslConnection;

public:
  Network();
  ~Network();

public:
  bool get(std::string host, std::string query);

public:
  std::string urlencode(const std::string &unescaped);

private:
  int _httpConnect(std::string host);
  void _httpClose(int socket);
  int _httpsConnect(std::string host);
  void _httpsClose(int socket);
  bool _send(char * buffer, int size);

private:
  std::string _getIp(std::string host);
};

} // end namespace countly

#endif
