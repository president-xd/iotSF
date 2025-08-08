#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>
#include <iomanip>
#include "wifi/usb/info_extractor.h"
#include "wifi/pci/pci_detector.h"
#include "wifi/wireless/info_extractor.h"

using namespace wifi::usb;
using namespace wifi::pci;
using namespace wifi::wireless;

static void print_usb_devices(const std::vector<USBDeviceInfo>& devs) {
    std::cout << "[USB Device] \n";
    std::cout << "----------------------------------------" << std::endl;
    bool first = true;
    for (const auto &d : devs) {
        if (!first) std::cout << "\n";
        first = false;
        // std::cout << "    {\n"
        //           << "      \"vendor_id\": \"" << std::hex << std::setw(4) << std::setfill('0') << d.vendor_id << std::dec << "\",\n"
        //           << "      \"product_id\": \"" << std::hex << std::setw(4) << std::setfill('0') << d.product_id << std::dec << "\",\n"
        //           << "      \"class\": " << d.device_class << ",\n"
        //           << "      \"subclass\": " << d.device_subclass << ",\n"
        //           << "      \"protocol\": " << d.device_protocol << ",\n"
        //           << "      \"manufacturer\": \"" << d.manufacturer << "\",\n"
        //           << "      \"product\": \"" << d.product << "\",\n"
        //           << "      \"serial\": \"" << d.serial << "\",\n"
        //           << "      \"bus\": \"" << d.bus_number << "\",\n"
        //           << "      \"address\": \"" << d.device_address << "\"\n"
        //           << "    }";

        std::cout << "Vendor ID: " << std::hex << std::setw(4) << std::setfill('0') << d.vendor_id << std::dec << std::endl;
        std::cout << "Product ID: " << std::hex << std::setw(4) << std::setfill('0') << d.product_id << std::dec << std::endl;
        std::cout << "Class: " << static_cast<int>(d.device_class) << std::endl;
        std::cout << "Subclass: " << static_cast<int>(d.device_subclass) << std::endl;
        std::cout << "Protocol: " << static_cast<int>(d.device_protocol) << std::endl;
        std::cout << "Manufacturer: " << d.manufacturer << std::endl;
        std::cout << "Product: " << d.product << std::endl;
        std::cout << "Serial: " << d.serial << std::endl;
        std::cout << "Bus Number: " << static_cast<int>(d.bus_number) << std::endl;
        std::cout << "Device Address: " << static_cast<int>(d.device_address) << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    std::cout << "Total USB devices found: " << devs.size() << std::endl;
}

// static void print_pci_devices(const std::vector<PCIDeviceInfo>& devs) {
//     std::cout << "{\n  \"pci_devices\": [\n";
//     bool first = true;
//     for (const auto &d : devs) {
//         if (!first) std::cout << ",\n";
//         first = false;
//         std::cout << "    {\n"
//                   << "      \"vendor_id\": \"" << std::hex << std::setw(4) << std::setfill('0') << d.vendor_id << std::dec << "\",\n"
//                   << "      \"device_id\": \"" << std::hex << std::setw(4) << std::setfill('0') << d.device_id << std::dec << "\",\n"
//                   << "      \"class\": \"" << d.class_name << "\",\n"
//                   << "      \"vendor_name\": \"" << d.vendor_name << "\",\n"
//                   << "      \"device_name\": \"" << d.device_name << "\"\n"
//                   << "    }";
//     }
//     std::cout << "\n  ]\n}\n";
// }


void print_wireless_info(InfoExtractor &extractor) {

    auto interfaces = extractor.list_interfaces();
    std::cout << "Wireless Interfaces:\n";
    for (auto& iface : interfaces) {
        auto info = extractor.get_info(iface);
        std::cout << "---------------------------------\n";
        std::cout << "Interface: " << info.interface_name << "\n";
        std::cout << "MAC: " << info.mac_address << "\n";
        std::cout << "Driver: " << info.driver << "\n";
        std::cout << "Protocol: " << info.wireless_protocol << "\n";
        std::cout << "Mode: " << info.mode << "\n";
        std::cout << "Frequency: " << info.frequency_mhz << " MHz\n";
        std::cout << "Channel: " << (int)info.channel << "\n";
        std::cout << "Tx Power: " << info.tx_power_dbm << " dBm\n";
        std::cout << "Signal: " << info.signal_level_dbm << " dBm\n";
        std::cout << "Link Quality: " << info.link_quality << "\n";
        std::cout << "Encryption: " << info.encryption << "\n";
    }
}

int main(/*int argc, char** argv*/) {
    std::cout << "iotSF - Device discovery module\n\n";

    try {
        // USBDetector usb;
        // auto usb_devs = usb.discover();
        // std::cout << "### USB devices (" << usb_devs.size() << " found) ###\n";
        // print_usb_devices(usb_devs);

        // std::cout << "\n";

        InfoExtractor extractor;
        std::cout << "### Wireless Interfaces ###\n";
        print_wireless_info(extractor);

        // PCIDetector pci;
        // auto pci_devs = pci.discover();
        // std::cout << "### PCI devices (" << pci_devs.size() << " found) ###\n";
        // print_pci_devices(pci_devs);
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}

