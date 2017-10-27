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

#include "countly/Device.h"

// http://stackoverflow.com/a/16859693

#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#ifdef __APPLE__
#include <net/if_dl.h>
#include <ifaddrs.h>
#include <net/if_types.h>
#else
#include <linux/if.h>
#include <linux/sockios.h>
#endif

std::string macAddress()
{
  unsigned char* macAddr;

#ifdef __APPLE__

  struct ifaddrs* ifaphead;

  if (getifaddrs(&ifaphead))
  {
    return "";
  }

  struct ifaddrs *ifap;
  for (ifap = ifaphead; ifap; ifap = ifap->ifa_next)
  {
    struct sockaddr_dl* sdl = (struct sockaddr_dl*)ifap->ifa_addr;
    if (sdl && (sdl->sdl_family == AF_LINK) && (sdl->sdl_type == IFT_ETHER))
    {
      macAddr = (unsigned char*)(LLADDR(sdl));
      break;
    }
  }

  freeifaddrs(ifaphead);

#else

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock < 0)
  {
    return "";
  }

  struct ifconf conf;
  char ifconfbuf[128 * sizeof(struct ifreq)];
  memset(ifconfbuf, 0, sizeof(ifconfbuf));
  conf.ifc_buf = ifconfbuf;
  conf.ifc_len = sizeof(ifconfbuf);
  if (ioctl(sock, SIOCGIFCONF, &conf))
  {
    return "";
  }

  struct ifreq* ifr;
  for (ifr = conf.ifc_req; (char*)ifr < (char*)conf.ifc_req + conf.ifc_len; ifr++)
  {
    if (ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data)
    {
      continue;
    }
    if (ioctl(sock, SIOCGIFFLAGS, ifr))
    {
      continue;
    }
    if (!ioctl(sock, SIOCGIFHWADDR, ifr))
    {
      macAddr = (unsigned char*)&(ifr->ifr_addr.sa_data);
      break;
    }
  }

  close(sock);

#endif

  if (macAddr == NULL) {
    return "";
  }

  std::ostringstream mac;
  mac.fill('0');
  mac << std::hex;
  for (unsigned int i = 0; i < 6; i++)
  {
    if (i != 0)
    {
      mac << ":";
    }
    mac << std::setw(2) << int(macAddr[i]);
  }
  return mac.str();
}

namespace countly
{

std::string Device::id()
{
  std::string mac = macAddress();

  if (mac == "") {
    return "unknown-device-id";
  }

  std::ostringstream h; //!OCLINT
  h << std::hash<std::string>{}(mac);
  return h.str();
}

} // end namespace countly
