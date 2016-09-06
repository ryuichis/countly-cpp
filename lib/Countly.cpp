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

#include "countly/Countly.h"
#include "countly/Network.h"

namespace countly
{

Countly::Countly()
{
  _network = new Network();
}

Countly::~Countly()
{
  delete _network;
}

void Countly::start(std::string host, std::string appKey)
{
  _host = host;
  _appKey = appKey;

  std::string query = "app_key=" + appKey +
    "&device_id=testdevice&sdk_version=16.06&begin_session=1";
  std::string metrics = R"body({
    "_os": "macOS",
    "_os_version": "Sierra",
    "_device": "Macbook Pro",
    "_resolution": "1280x800",
    "_app_version": "0.1"
})body";

  std::string path = "/i?" + query + "&metrics=" + _network->urlencode(metrics);
  _network->get(_host, path);
}

void Countly::suspend()
{
  std::string path = "/i?app_key=" + _appKey +
    "&device_id=testdevice&sdk_version=16.06&end_session=1";
  _network->get(_host, path);
}

void Countly::recordEvent(std::string eventKey)
{
}

} // end namespace countly
