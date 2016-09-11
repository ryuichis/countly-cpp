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
#include "countly/Metrics.h"
#include "countly/Device.h"
#include "countly/Event.h"

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

  std::string metrics = Metrics::toJson();

  std::string path = queryPrefix() +
    "&begin_session=1&metrics=" + _network->urlencode(metrics);
  _network->get(_host, path);
}

void Countly::suspend()
{
  std::string path = queryPrefix() + "&end_session=1";
  _network->get(_host, path);
}

void Countly::recordEvent(std::string eventKey)
{
  Event event(eventKey);
  std::string events = "[" + event.toJson() + "]";
  std::string path = queryPrefix() + "&events=" + _network->urlencode(events);
  _network->get(_host, path);
}

void Countly::recordEvent(std::string eventKey,
  std::map<std::string, std::string> segmentation)
{
  Event event(eventKey, segmentation);
  std::string events = "[" + event.toJson() + "]";
  std::string path = queryPrefix() + "&events=" + _network->urlencode(events);
  _network->get(_host, path);
}

std::string Countly::queryPrefix()
{
  std::string prefix = "/i?app_key=" + _appKey + "&device_id=" + Device::id();
  return prefix;
}

} // end namespace countly
