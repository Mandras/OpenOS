#!/bin/sh

sudo userdel -rf openos

sudo adduser openos --disabled-password --quiet --no-create-home --uid 5220 --gecos OPENOS --system

