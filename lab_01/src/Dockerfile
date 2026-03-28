FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    nano \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY write_date.sh /app/write_date.sh
RUN chmod +x /app/write_date.sh

RUN useradd -m -s /bin/bash docker_user && \
    echo "docker_user:docker_pass" | chpasswd

WORKDIR /home/docker_user
CMD ["/bin/bash"]
