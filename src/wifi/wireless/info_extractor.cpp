#include "wifi/wireless/info_extractor.h"
#include <iostream>
#include <sstream>
#include <array>
#include <memory>
#include <cstdio>

namespace wifi::wireless {

// Helper to run a shell command and capture output
static std::string run_command(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::vector<std::string> InfoExtractor::list_interfaces() {
    std::vector<std::string> interfaces;
    std::string output = run_command("iw dev | grep Interface | awk '{print $2}'");
    std::istringstream iss(output);
    std::string iface;
    while (iss >> iface) {
        interfaces.push_back(iface);
    }
    return interfaces;
}

WirelessInfo InfoExtractor::get_info(const std::string& iface) {
    WirelessInfo info;
    info.interface_name = iface;

    // MAC address
    info.mac_address = run_command("cat /sys/class/net/" + iface + "/address");
    info.mac_address.erase(info.mac_address.find_last_not_of(" \n\r\t")+1);

    // Driver
    info.driver = run_command("basename $(readlink /sys/class/net/" + iface + "/device/driver)");
    info.driver.erase(info.driver.find_last_not_of(" \n\r\t")+1);

    // Mode, Frequency, etc. (from iwconfig)
    std::string iwout = run_command("iwconfig " + iface + " 2>/dev/null");
    std::istringstream iwss(iwout);
    std::string line;
    while (std::getline(iwss, line)) {
        if (line.find("IEEE") != std::string::npos) {
            size_t pos = line.find("IEEE");
            info.wireless_protocol = line.substr(pos, line.find(' ', pos+5) - pos);
        }
        if (line.find("Mode:") != std::string::npos) {
            size_t pos = line.find("Mode:") + 5;
            info.mode = line.substr(pos, line.find(' ', pos) - pos);
        }
        if (line.find("Frequency:") != std::string::npos) {
            size_t pos = line.find("Frequency:") + 10;
            info.frequency_mhz = std::stod(line.substr(pos)) * 1000;
        }
        if (line.find("Tx-Power=") != std::string::npos) {
            size_t pos = line.find("Tx-Power=") + 9;
            info.tx_power_dbm = std::stoi(line.substr(pos));
        }
        if (line.find("Link Quality=") != std::string::npos) {
            size_t pos = line.find("Link Quality=") + 13;
            info.link_quality = std::stoi(line.substr(pos, line.find('/', pos) - pos));
        }
        if (line.find("Signal level=") != std::string::npos) {
            size_t pos = line.find("Signal level=") + 13;
            info.signal_level_dbm = std::stoi(line.substr(pos));
        }
    }

    // Channel
    std::string chan = run_command("iwlist " + iface + " channel | grep Current | awk '{print $2}'");
    if (!chan.empty()) info.channel = std::stoi(chan);

    // Encryption (simplified check)
    std::string sec = run_command("iwlist " + iface + " encryption | grep -i 'Encryption key'");
    info.encryption = (sec.find("off") != std::string::npos) ? "None" : "Enabled";

    return info;
}

} // namespace wifi::wireless
