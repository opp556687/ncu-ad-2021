FROM ubuntu:20.04
MAINTAINER opp556687

RUN apt-get update
RUN apt-get install xinetd -qy
RUN useradd -m pekopeko
RUN chown -R root:root /home/pekopeko
RUN chmod -R 755 /home/pekopeko

CMD ["/usr/sbin/xinetd","-dontfork"]
