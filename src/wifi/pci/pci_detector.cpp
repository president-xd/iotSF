#include "wifi/pci/pci_detector.h"
#include <pci/pci.h>
#include <iostream>
#include <vector>
#include <cstring>

namespace wifi::pci {

std::vector<PCIDeviceInfo> PCIDetector::discover() {
    std::vector<PCIDeviceInfo> out;

    struct pci_access* pacc = pci_alloc();
    if (!pacc) {
        std::cerr << "[pci] pci_alloc failed\n";
        return out;
    }
    pci_init(pacc);
    pci_scan_bus(pacc);

    for (struct pci_dev* dev = pacc->devices; dev; dev = dev->next) {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_CLASS);
        PCIDeviceInfo info{};
        info.vendor_id = dev->vendor_id;
        info.device_id = dev->device_id;
        info.device_class = dev->device_class;

        char vendor_buf[1024] = {0};
        char device_buf[1024] = {0};
        char class_buf[1024] = {0};

        pci_lookup_name(pacc, vendor_buf, sizeof(vendor_buf), PCI_LOOKUP_VENDOR, dev->vendor_id);
        pci_lookup_name(pacc, device_buf, sizeof(device_buf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
        pci_lookup_name(pacc, class_buf, sizeof(class_buf), PCI_LOOKUP_CLASS, dev->device_class);

        info.vendor_name = vendor_buf;
        info.device_name = device_buf;
        info.class_name = class_buf;

        out.push_back(std::move(info));
    }

    pci_cleanup(pacc);
    return out;
}

} // namespace wifi::pci
