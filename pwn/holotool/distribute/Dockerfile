FROM ubuntu:20.04
MAINTAINER opp556687

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m holotool
RUN chown -R root:root /home/holotool
RUN chmod -R 755 /home/holotool

CMD ["/usr/sbin/xinetd","-dontfork"]
