FROM ubuntu:20.04
MAINTAINER JyunD

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m gawr_gura
RUN chown -R root:root /home/gawr_gura
RUN chmod -R 755 /home/gawr_gura

CMD ["/usr/sbin/xinetd","-dontfork"]
