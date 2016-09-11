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

#ifndef COUNTLY_EVENT_H
#define COUNTLY_EVENT_H

#include <string>
#include <map>

namespace countly
{

class Event
{
private:
  std::string _key;
  int _count;
  std::map<std::string, std::string> _segmentation;

public:
  Event(std::string key,
    int count, std::map<std::string, std::string> segmentation);
  Event(std::string key);
  Event(std::string key, std::map<std::string, std::string> segmentation);

public:
  std::string toJson();
};

} // end namespace countly

#endif
