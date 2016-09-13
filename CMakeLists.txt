# Copyright 2016 Ryuichi Saito, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(COUNTLY)

SET(CMAKE_DISABLE_SOURCE_CHANGES ON)
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_MACOSX_RPATH ON)
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

IF(APPLE)
  SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
ELSE()
  IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS "-stdlib=libstdc++ ${CMAKE_CXX_FLAGS}")
  ENDIF()
  SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL "Release")
  SET(CMAKE_CXX_FLAGS "-O3 -DNDEBUG ${CMAKE_CXX_FLAGS}")
ELSE()
  SET(CMAKE_CXX_FLAGS "-O0 -g ${CMAKE_CXX_FLAGS}")
ENDIF()

IF(APPLE)
  # use OpenSSL from Homebrew installation due to Apple deprecated its support
  INCLUDE_DIRECTORIES(/usr/local/opt/openssl/include)
  LINK_DIRECTORIES(/usr/local/opt/openssl/lib)
ENDIF()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(lib)

ADD_EXECUTABLE(test-countly
  main.cpp
)

TARGET_LINK_LIBRARIES(test-countly
  Countly
  ssl
  crypto
)
