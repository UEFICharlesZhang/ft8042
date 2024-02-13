sudo dkms remove -m ft8042 -v 0.1
sudo rm -rf /usr/src/ft8042-0.1
sudo mkdir /usr/src/ft8042-0.1
sudo cp dkms.conf  /usr/src/ft8042-0.1/
sudo cp ft8042.c  /usr/src/ft8042-0.1/
sudo cp ft8042.h  /usr/src/ft8042-0.1/
sudo cp Makefile  /usr/src/ft8042-0.1/
sudo cp paramter.h  /usr/src/ft8042-0.1/
sudo dkms add -m ft8042 -v 0.1
sudo dkms install -m ft8042 -v 0.1
