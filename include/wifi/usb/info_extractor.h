#ifndef WIFI_USB_INFO_EXTRACTOR_H
#define WIFI_USB_INFO_EXTRACTOR_H

#include <string>
#include <vector>
#include <cstdint>

namespace wifi::usb {

struct USBDeviceInfo {
    uint16_t vendor_id;
    uint16_t product_id;
    uint8_t device_class;      // USB class code
    uint8_t device_subclass;   // USB subclass code
    uint8_t device_protocol;   // USB protocol code
    std::string manufacturer;
    std::string product;
    std::string serial;
    uint8_t bus_number;        // Bus number
    uint8_t device_address;    // Device address
};

class USBDetector {
public:
    USBDetector() = default;
    ~USBDetector() = default;

    std::vector<USBDeviceInfo> discover();
};

} // namespace wifi::usb

#endif // WIFI_USB_INFO_EXTRACTOR_H
