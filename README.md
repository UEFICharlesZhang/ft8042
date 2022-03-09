# ft8042
Keyboard and mouse driver for phytium platform notebooks

## How to build
```bash
make
sudo make install
```

## dkms build
```bash
sudo cp ft8042 /usr/src/ft8042-0.1/
sudo dkms add -m ft8042
sudo dkms build -m ft8042 -v 0.1
sudo dkms install -m ft8042 -v 0.1
```