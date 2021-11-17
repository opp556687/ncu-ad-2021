FROM ubuntu:20.04
MAINTAINER opp556687

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m holoshell
RUN chown -R root:root /home/holoshell
RUN chmod -R 755 /home/holoshell

CMD ["/usr/sbin/xinetd","-dontfork"]