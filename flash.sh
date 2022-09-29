#!/bin/sh

docker run --rm -it --net=host --device /dev/ttyUSB0 -v $PWD:/config petewall/platformio:6.1.4 run --project-dir /config -t upload
