#!/usr/bin/env bash

trap 'echo ">> $BASH_COMMAND"' DEBUG

files="main.ino global.h global.cpp can/can.h can/can.cpp pubbuff/pubbuff.h pubbuff/pubbuff.cpp"

# Compile device Matt
particle flash Matt $files # main.ino global.h global.cpp cmd/*.*h cmd/*.*cpp can/can.h can/can.cpp pubbuff/pubbuff.h pubbuff/pubbuff.cpp
if [ $? -eq 1 ]; then # Check if compile failed
    exit 1
fi

particle flash Parker $files
sleep 20s # 15s is enough to flash device

# A message under 32 characters is prefered because particle.io allows for a
# device to publish 4 events in rapid succession. It will then prevent them
# from sending more for a few seconds
particle publish "can@100" "Creates len/8 events on receiver" --private
sleep 5s

particle publish "can@10" "I can now send a very, very, very long string over CAN by using the pubbuff cpp module. It allows strings up to 1024 bytes." --private
sleep 5s

particle publish "can" "1122334455667788" --private
sleep 5s

particle publish "can" "48656c6c6f205061726b6572" --private
sleep 5s
