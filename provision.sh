#!/usr/bin/env bash

# Installing dependencies
apt-get update && apt-get install cryptsetup zsh -y

# Moving scripts
mv /tmp/init_container.sh /usr/sbin/init_container.sh
chmod 755 /usr/sbin/init_container.sh
mv /tmp/umount_container.sh /usr/sbin/umount_container.sh
chmod 755 /usr/sbin/umount_container.sh

mv /tmp/pamela.so /lib/x86_64-linux-gnu/security/pamela.so

# Creating users
useradd rotta_f -m -p $(perl -e 'print crypt("rotta_f", "password")')
gpasswd -a rotta_f sudo
touch /home/rotta_f/.zshrc

useradd sommer_q -m -p $(perl -e 'print crypt("sommer_q", "password")')
gpasswd -a sommer_q sudo
touch /home/sommer_q/.zshrc

# SSH Password login Authorization
sed -i "/PasswordAuthentication no/c\PasswordAuthentication yes" /etc/ssh/sshd_config
service ssh restart

# Regisering PAM module
echo "auth required pamela.so" >> /etc/pam.d/common-auth
echo "session required pamela.so" >> /etc/pam.d/common-auth

echo "DAMN SON, Ready to fire"
