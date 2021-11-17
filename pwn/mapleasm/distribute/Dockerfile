FROM ubuntu:20.04
MAINTAINER maple3142

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m mapleasm
RUN chown -R root:root /home/mapleasm
RUN chmod -R 755 /home/mapleasm

CMD ["/usr/sbin/xinetd","-dontfork"]
