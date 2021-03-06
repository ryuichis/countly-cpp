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

#include "countly/Countly.h"

#include <iostream>

using namespace std;
using namespace countly;

int main(int argc, const char **argv)
{
  if (argc < 3)
  {
    cout << "Usage: " << argv[0] << " <host> <app key>" << endl;
    return -1;
  }

  Countly countly;
  countly.start(argv[1], argv[2]);
  countly.recordEvent("TestEvent1");
  countly.recordEvent("TestEvent2", {{"TestSegment1", "foo"}, {"TestSegment2", "bar"}});
  countly.recordEvent("TestEvent2", {{"TestSegment1", "apple"}, {"TestSegment2", "banana"}});
  countly.recordEvent("日本語");
  countly.recordEvent("简体中文");
  countly.recordEvent("繁體中文");
  countly.suspend();

  return 0;
}
