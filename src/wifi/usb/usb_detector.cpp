#include "wifi/usb/usb_detector.h"
#include <libusb-1.0/libusb.h>
#include <iostream>
#include <sstream>

namespace wifi::usb {

static std::string safe_get_string(libusb_device_handle* h, uint8_t idx) {
    if (!h || idx == 0) return "";
    unsigned char buf[256];
    int ret = libusb_get_string_descriptor_ascii(h, idx, buf, sizeof(buf));
    return ret > 0 ? std::string(reinterpret_cast<char*>(buf), ret) : "";
}

std::vector<USBDeviceInfo> USBDetector::discover() {
    std::vector<USBDeviceInfo> out;
    libusb_context* ctx = nullptr;
    libusb_device** list = nullptr;

    if (libusb_init(&ctx) < 0) {
        std::cerr << "[USB] libusb init failed\n";
        return out;
    }

    ssize_t cnt = libusb_get_device_list(ctx, &list);
    if (cnt < 0) {
        std::cerr << "[USB] get device list failed\n";
        libusb_exit(ctx);
        return out;
    }

    for (ssize_t i = 0; i < cnt; ++i) {
        libusb_device* dev = list[i];
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(dev, &desc) != 0) continue;

        USBDeviceInfo info{};
        info.vendor_id       = desc.idVendor;
        info.product_id      = desc.idProduct;
        info.device_class    = desc.bDeviceClass;
        info.device_subclass = desc.bDeviceSubClass;
        info.device_protocol = desc.bDeviceProtocol;
        info.bus_number      = libusb_get_bus_number(dev);
        info.device_address  = libusb_get_device_address(dev);

        libusb_device_handle* handle = nullptr;
        if (libusb_open(dev, &handle) == 0) {
            info.manufacturer = safe_get_string(handle, desc.iManufacturer);
            info.product      = safe_get_string(handle, desc.iProduct);
            info.serial       = safe_get_string(handle, desc.iSerialNumber);
            libusb_close(handle);
        }

        out.push_back(std::move(info));
    }

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    return out;
}

} // namespace wifi::usb
