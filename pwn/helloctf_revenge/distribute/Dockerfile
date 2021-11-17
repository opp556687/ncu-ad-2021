FROM ubuntu:20.04
MAINTAINER JyunD

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m helloctf_revenge
RUN chown -R root:root /home/helloctf_revenge
RUN chmod -R 755 /home/helloctf_revenge

CMD ["/usr/sbin/xinetd","-dontfork"]
