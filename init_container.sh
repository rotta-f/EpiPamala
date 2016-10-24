#!/usr/bin/env bash

# $1 = user
# $2 = path to file containing user password

home="/home/$1"
filename=".container"
filepath="$home/$filename"

# $1 user
# $2 user's home
function createDir() {
  #echo "mkdir $home/container"
  mkdir "$2/container"

  echo "Mounting to $2/container"
  mount "/dev/mapper/$1_secret_container" "$2/container"

  #echo "chown $login $home/container"
  chown $1 "$2/container"
  chmod 700 "$2/container"
}

echo "Init Container"

if [ ! -f "$filepath" ]; then
  echo "Creating 100MB file in $filepath..."
  fallocate -l 100MB $filepath
  chmod 700 "$filepath"

  #echo "luksFormat $filepath"
  cat $2 | cryptsetup -q luksFormat $filepath

  #echo "luksOpen $filepath $1_secret_container"
  cat $2 | cryptsetup luksOpen $filepath "$1_secret_container"

  #echo "mkfs /dev/mapper/$1_secret_container"
  mkfs.ext4 -q "/dev/mapper/$1_secret_container"

  createDir $1 $home
else
  echo "File $filepath already exist"
  cat $2 | cryptsetup luksOpen $filepath "$1_secret_container"

  createDir $1 $home
fi
