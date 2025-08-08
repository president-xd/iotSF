### WIFI Module:

sudo apt update
sudo apt install ethtool usbutils pciutils

sudo apt update
sudo apt install build-essential cmake libusb-1.0-0-dev libpci-dev libnl-3-dev libnl-genl-3-dev

sudo apt install libudev-dev


sudo apt install libusbp-dev pkg-config
pkg-config --cflags --libs libusbp-1
sudo apt install git cmake g++ pkg-config
git clone https://github.com/pololu/libusbp.git
cd libusbp
mkdir build && cd build
cmake ..
make
sudo make install

sudo apt install wireless-tools
