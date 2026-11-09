FROM debian:9

RUN echo "deb http://archive.debian.org/debian stretch main" > /etc/apt/sources.list \
    && apt-get update -o Acquire::Check-Valid-Until=false && apt-get install -y \
    gcc \
    make \
    inetutils-ping \
    net-tools \
    iproute2 \
    sudo \
    valgrind \
    strace \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ft_ping

CMD ["/bin/bash"]