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

#include "countly/Event.h"

namespace countly
{

Event::Event(std::string key,
  int count, std::map<std::string, std::string> segmentation)
{
  _key = key;
  _count = count;
  _segmentation = segmentation;
}

Event::Event(std::string key): Event::Event(key, 1, {}) {}
Event::Event(std::string key, std::map<std::string, std::string> segmentation):
  Event::Event(key, 1, segmentation) {}

std::string Event::toJson()
{
  std::string json = "{";
  json += "\"key\":\"" + _key + "\"";
  json += ",\"count\":" + std::to_string(_count);

  if (_segmentation.size() > 0) {
    json += ",\"segmentation\":{";
    std::map<std::string, std::string>::iterator i = _segmentation.begin(); //!OCLINT
    while (i != _segmentation.end())
    {
      json += "\"" + i->first + "\":\"" + i->second + "\"";
      i++;
      if (i != _segmentation.end()) {
        json += ",";
      }
    }
    json += "}";
  }

  json += "}";

  return json;
}

} // end namespace countly
