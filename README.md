# countly-cpp

countly-cpp is a lightweight C++ library for [Countly](http://count.ly).

It is designed to have minimal dependencies, and aim to be the drop in solution for C++ projects on various environments.

* * *

## A Work In Progress

countly-cpp is still in early development. Many requirements in [Countly SDK development guidance](http://resources.count.ly/docs/sdk-development-guide) are pending for implementations.

### Features

- Initialization
  - [ ] countly cloud
  - [ ] http host
  - [x] https host
  - [ ] port
  - [x] app key
  - [ ] device id
  - [ ] country code
  - [ ] city
  - [ ] location
- Session flows
  - [x] begin session
  - [ ] session duration
  - [x] end session
- Device metrics
  - [ ] os
  - [ ] os version
  - [ ] device
  - [ ] resolution
  - [ ] carrier
  - [ ] app version
  - [ ] density
  - [ ] locale
  - [ ] store
- Events
  - [x] key (count value defaults to 1 internally if not specified)
  - [ ] key/count
  - [ ] key/sum
  - [ ] key/duration
  - [ ] key/count/sum
  - [ ] key/segmentation
  - [ ] key/segmentation/count
  - [ ] key/segmentation/count/sum
  - [ ] key/segmentation/count/sum/duration
- Timed events
  - [ ] start event (key)
  - [ ] end event (key/segmentation/count/sum)
  - [ ] end event (key)
- Device
  - [ ] custom device id
  - [ ] change device id

### Technical

- Environments
  - [x] Linux
  - [x] macOS
  - [ ] Windows
- Event
  - [ ] Queuing
  - [ ] Storage
  - [x] Networking

## Dependencies

* OpenSSL

## Usage

Check out the [main.cpp](main.cpp) in this repository for examples.

## Contact

Ryuichi Saito

- http://github.com/ryuichis
- ryuichi@ryuichisaito.com

## License

countly-cpp is available under the Apache License 2.0.
See the [LICENSE](LICENSE) file for more info.
