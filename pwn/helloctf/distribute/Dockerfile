FROM ubuntu:20.04
MAINTAINER JyunD

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m helloctf
RUN chown -R root:root /home/helloctf
RUN chmod -R 755 /home/helloctf

CMD ["/usr/sbin/xinetd","-dontfork"]
