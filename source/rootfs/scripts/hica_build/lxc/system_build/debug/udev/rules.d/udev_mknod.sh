#!/bin/sh

if [ -e /dev/$1 ]; then
	rm -fr /dev/$1
fi

if [ "$SUBSYSTEM" == "block" ]; then
	mknod /dev/$1 b $MAJOR $MINOR
else
	mknod /dev/$1 c $MAJOR $MINOR
fi
