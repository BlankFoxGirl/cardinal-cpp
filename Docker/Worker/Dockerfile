FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install -y libhiredis-dev
COPY build/bin/libredis++.so.1 /usr/lib/
RUN ldconfig

RUN mkdir /app
WORKDIR /app

RUN ln -s /app/libcardinal.so /usr/lib/libcardinal.so

CMD sleep 10 && ./cardinal-server