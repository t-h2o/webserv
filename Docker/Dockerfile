FROM alpine:3.14

RUN apk add g++
RUN apk add make
RUN apk add valgrind
RUN apk add clang

RUN mkdir /paul
RUN mkdir /script

COPY entrypoint.sh /script

WORKDIR /paul

ENTRYPOINT ["/script/entrypoint.sh"]
