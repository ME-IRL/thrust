#!/bin/bash

while :; do
	echo Waiting
	[ -c /dev/ttyACM0 ] && break
done

echo Uploading
./upload hex:i
#/home/brian/Downloads/arduino-1.8.8/arduino --upload empty.ino
