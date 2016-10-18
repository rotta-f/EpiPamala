#!/usr/bin/env bash

home="/home/$1"
filename=".container"
filepath="$home/$filename"

echo "Unmounting $home/container"
umount "$home/container"
cryptsetup luksClose "$1_secret_container"
