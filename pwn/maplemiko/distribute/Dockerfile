FROM ubuntu:20.04
MAINTAINER maple3142

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m maplemiko
RUN chown -R root:root /home/maplemiko
RUN chmod -R 755 /home/maplemiko

CMD ["/usr/sbin/xinetd","-dontfork"]
