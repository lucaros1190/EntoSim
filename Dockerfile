FROM centos

COPY /EntoSim-2.1 /home/EntoSim-2.1
WORKDIR /home/EntoSim-2.1

LABEL maintainer="luca.rossini@unitus.it"
LABEL maintainer="silvia.turco@unitus.it"

RUN yum update -y 
RUN yum install -y epel-release 
RUN yum install -y python3
RUN yum install -y git
RUN git clone https://github.com/lucaros1190/EntoSim-2.1.git
RUN dnf group install -y "Development Tools"
RUN yum -y install root
RUN make all 
RUN make python.pkg
EXPOSE 80
ENV PATH="${PATH}:/home/EntoSim-2.1/"

