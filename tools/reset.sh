#!/bin/bash

while :; do
	echo Waiting
	[ -c /dev/ttyACM0 ] && break
done

echo Uploading
tools/upload tools/empty.hex
#/home/brian/Downloads/arduino-1.8.8/arduino --upload empty.ino
