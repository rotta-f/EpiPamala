#!/usr/bin/env bash

home="/home/$1"
filename=".container"
filepath="$home/$filename"

echo "Init Container"
echo $filepath

if [ ! -f ~/container ]; then
  echo "Creating file $filepath"
  fallocate -l 50MB $filepath
  echo $2 | cryptsetup -q luksFormat $filepath
  echo $2 | cryptsetup luksOpen $filepath secret_container
  mkfs.ext4 /dev/mapper/secret_container
  mkdir "$home/container"
  mount /dev/mapper/secret_container ~/container

else
  echo "File $filepath already exist, mounting"
  cryptsetup luksOpen $filepath secret_container
  mount /dev/mapper/secret_container ~/container
  exit
fi
