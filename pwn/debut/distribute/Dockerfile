FROM ubuntu:20.04
MAINTAINER opp556687

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m debut
RUN chown -R root:root /home/debut
RUN chmod -R 755 /home/debut

CMD ["/usr/sbin/xinetd","-dontfork"]
