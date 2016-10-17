#!/usr/bin/env bash

home="/home/$1"
filename=".container"
filepath="$home/$filename"

echo "Umount Container"
echo "unmounting $home/container"
umount "$home/container"
cryptsetup luksClose "secret_container"
