FROM archlinux:latest

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm clang
RUN pacman -S --noconfirm make

RUN mkdir /documents

WORKDIR /documents

ENTRYPOINT ["/usr/bin/make", "format"]
