# Cardinal Code C++
[![CodeQL](https://github.com/sarahjabado/cardinal-cpp/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/sarahjabado/cardinal-cpp/actions/workflows/codeql.yml)

A C++ Rewrite of the original Cardinal Core for improved performance.

### How to start;
1. Install Docker.
1. Run the Cardinal C++ Compiler Docker Repo to build the docker image.
1. Run `./dev up` within this repository.

Note: Cardinal is designed to compile and run as a docker images / containers. It is not designed to run on a standalone linux system, however, the Cardinal binary file is compiled using docker containers from linux images, this means that with some minor tweaking to the dockerfile you can build Cardinal for your target platform with relative ease.