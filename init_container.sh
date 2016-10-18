#!/usr/bin/env bash

home="/home/$1"
filename=".container"
filepath="$home/$filename"

echo "Init Container"

if [ ! -f "$filepath" ]; then
  echo "Creating 100MB file in $filepath..."
  fallocate -l 100MB $filepath

  #echo "luksFormat $filepath"
  cat $2 | cryptsetup -q luksFormat $filepath

  #echo "luksOpen $filepath $1_secret_container"
  cat $2 | cryptsetup luksOpen $filepath "$1_secret_container"

  #echo "mkfs /dev/mapper/$1_secret_container"
  mkfs.ext4 -q "/dev/mapper/$1_secret_container"

  #echo "mkdir $home/container"
  mkdir "$home/container"

  echo "Mounting to $home/container"
  #echo "mount /dev/mapper/$1_secret_container to $home/container"
  mount "/dev/mapper/$1_secret_container" "$home/container"

  #echo "chown $1 $home/container"
  chown $1 "$home/container"
else
  echo "File $filepath already exist"
  cat $2 | cryptsetup luksOpen $filepath "$1_secret_container"

  echo "Mounting to $home/container"
  mount "/dev/mapper/$1_secret_container" "$home/container"
fi
