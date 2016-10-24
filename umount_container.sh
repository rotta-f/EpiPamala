#!/usr/bin/env bash

home="/home/$1"
filename=".container"
filepath="$home/$filename"

echo "Unmounting $home/container"
umount "$home/container"
cryptsetup luksClose "$1_secret_container"

echo "Removing $home/container"
#echo "rm -rf $home/container"
rm -rf "$home/container"
