#ifndef WIFI_PCI_PCI_DETECTOR_H
#define WIFI_PCI_PCI_DETECTOR_H

#include <string>
#include <vector>

namespace wifi::pci {

struct PCIDeviceInfo {
    unsigned int vendor_id;
    unsigned int device_id;
    unsigned int device_class;
    std::string vendor_name;
    std::string device_name;
    std::string class_name;
};

class PCIDetector {
public:
    PCIDetector() = default;
    ~PCIDetector() = default;

    std::vector<PCIDeviceInfo> discover();
};

} // namespace wifi::pci

#endif // WIFI_PCI_PCI_DETECTOR_H
