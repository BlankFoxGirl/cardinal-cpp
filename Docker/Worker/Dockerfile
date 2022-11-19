FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y libhiredis-dev
COPY build/bin/libredis++.so.1 /usr/lib/
RUN ldconfig

RUN mkdir /app
WORKDIR /app

CMD ./myexample