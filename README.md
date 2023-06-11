# Cardinal Code C++
[![CodeQL](https://github.com/sarahjabado/cardinal-cpp/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/sarahjabado/cardinal-cpp/actions/workflows/codeql.yml)

A C++ Rewrite of the original Cardinal Core for improved performance.

## How to start;

### Docker Compose (Recommended for Integration Testing)
1. Install Docker.
1. Run the Cardinal C++ Compiler Docker Repo to build the docker image.
1. Run `./dev up` within this repository.

### Local Build and Run (Recommended for Development [Quick and Dirty])
1. Install CLang C++ Compiler with support for C++ 17.
1. Run command `./dev run`

### Additional Commands:
- `./dev ninja` Cleans the build directory and refreshes CMakeLists for PowerTech C++ VSCode Extension.
- `./dev clean` Cleans the build directory.
- `./dev down` Docker Compose wrapper command which tears down the DC Project.
- `./dev up` Docker Compose wrapper command which instantiates the DC Project.
- `./dev install_modules` Downloads dependency repos into the vendor file. Currently does not support downloading boost::di.
- `./dev install` Alias of install_modules, see above.
- `./dev build` Builds all dependencies if not previously built. Compiles cardinal-server binary file.
- `./dev run` Runs the build command, and then executes the _~/build/bin/cardinal-server_ binary file.
- `./dev test` Runs the UnitTest suite based on UnitTest-CPP.

## Dependencies:
- Cardinal uses Redis++ which has a library dependency for Hiredis, you must install hiredis before you can build Cardinal or Redis++. [Hiredis Official Repo](https://github.com/redis/hiredis)
- Cardinal may not compile in certain C++ compilers, it is recommended to use CLang to compiler as Cardinal was designed and tested using CLang, there are known issues with g++.
- Cardinal is designed to use docker (recommended) for containerisation. However Containerd and Rancher should be adequate.
- Cardinal comes with its own Docker Image to manage compilation for containerized environments, please refer to [Cardinal-Compiler on Docker Hub](https://hub.docker.com/r/sarahjabado/cardinal-compiler). Source Code: [Cardinal-Compiler Repo](https://github.com/sarahjabado/cardinal-compiler)
- Boost::DI Header Library for Dependency Injection.
- UnitTest C++ for Test Library.
- Eranpeer/FakeIt for Mock Library.

Note: Cardinal is designed to compile and run as a docker images / containers. It is not designed to run on a standalone linux system, however, the Cardinal binary file is compiled using docker containers from linux images, this means that with some minor tweaking to the dockerfile you can build Cardinal for your target platform with relative ease.