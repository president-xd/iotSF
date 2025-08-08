#ifndef WIFI_WIRELESS_INFO_EXTRACTOR_H
#define WIFI_WIRELESS_INFO_EXTRACTOR_H

#include <string>
#include <vector>
#include <cstdint>

namespace wifi::wireless {

struct WirelessInfo {
    std::string interface_name;
    std::string mac_address;
    std::string driver;
    std::string wireless_protocol;
    std::string mode;
    uint32_t frequency_mhz;
    uint8_t channel;
    int32_t tx_power_dbm;
    int32_t signal_level_dbm;
    int32_t link_quality;
    std::string encryption;
};

class InfoExtractor {
public:
    InfoExtractor() = default;
    ~InfoExtractor() = default;

    // List all wireless interfaces
    std::vector<std::string> list_interfaces();

    // Get detailed info about a specific interface
    WirelessInfo get_info(const std::string& iface);
};

} // namespace wifi::wireless

#endif // WIFI_WIRELESS_INFO_EXTRACTOR_H
