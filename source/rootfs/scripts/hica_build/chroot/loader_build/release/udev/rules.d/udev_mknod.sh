#!/bin/sh
if [ "$SUBSYSTEM" == "block" ]; then
	mknod /home/stb/dev/$1 b $MAJOR $MINOR
	mknod /dev/$1 b $MAJOR $MINOR
else
	mknod /home/stb/dev/$1 c $MAJOR $MINOR
	mknod /dev/$1 c $MAJOR $MINOR
fi
	
chown -R 1000:1000 /home/stb/dev
chmod -R 0660 /home/stb/dev/*
