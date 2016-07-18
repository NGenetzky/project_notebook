# Modified from acencini/rpi-python-serial-wiringpi

# Pull base image
FROM resin/rpi-raspbian:wheezy
MAINTAINER Nathan Genetzky <nathan@genetzky.us>

# Install dependencies
RUN apt-get update && apt-get install -y \
    git-core \
    build-essential \
    gcc \
    python \
    python-dev \
    python-pip \
    python-virtualenv \
    --no-install-recommends && \
    rm -rf /var/lib/apt/lists/*

# Install Python Libraries
RUN pip install pyserial \
    spyrk \
    RPi.GPIO 


# Do not include wiring pi
    # RUN git clone git://git.drogon.net/wiringPi
    # RUN cd wiringPi && ./build
    # RUN pip install wiringpi2

# Env variables
ENV PARTICLE_ACCESS_TOKEN=null

# Define working directory
WORKDIR /workspace
ADD * /host/src/


# Define default command
CMD ["bash"]

# Start up Python Script
# RUN bash -c 'echo "firefox" >> /.bashrc'

# Recommended bash script to run
#!/bin/bash
#docker run  -v '/root/doorman':'/workspace/host/doorman' \
#        --device /dev/ttyAMA0:/dev/ttyAMA0 --device /dev/mem:/dev/mem \
#        --privileged --net=host -ti \
#         -e PARTICLE_ACCESS_TOKEN='YOUR_TOKEN' \
#         ngenetzky/doorman-doug /bin/bash 
