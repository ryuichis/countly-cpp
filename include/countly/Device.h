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

#ifndef COUNTLY_DEVICE_H
#define COUNTLY_DEVICE_H

#include <string>

namespace countly
{

class Device
{
public:
  // we use the hashed string of this network card's mac address
  // for both uniqueness and privacy protection
  static std::string id();
};

} // end namespace countly

#endif
