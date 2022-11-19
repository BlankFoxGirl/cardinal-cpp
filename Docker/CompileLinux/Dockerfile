FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y g++ make cmake libhiredis-dev

RUN mkdir /app
WORKDIR /app

CMD ./dev build