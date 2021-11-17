FROM ubuntu:20.04
MAINTAINER JyunD

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m peko
RUN chown -R root:root /home/peko
RUN chmod -R 755 /home/peko

CMD ["/usr/sbin/xinetd","-dontfork"]
