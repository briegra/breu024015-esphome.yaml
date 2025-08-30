#include "esphome.h"
#include <map>

class APNameTemplate : public Component, public TextSensor {
 public:
  TextSensor *bssid_sensor;

  // AP-Tabelle mit BSSID ? Name
  std::map<std::string, std::string> ap_map = {
    {"xx:yy:zz:aa:bb:cc", "Dummy"},
    {"62:62:8B:00:1D:42", "Garage"},
    {"6E:FF:7B:F2:67:66", "Lammellendach"},
    {"82-F1-7E-74-F6-10", "Lounge"},
    {"EA:C3:2A:9C:1A:B0", "Technik"},
    {"24:2F:D0:DF:4E:1C", "Grillplatz"},
    {"2E:2F:D0:DF:4E:1C", "Grillplatz"},
    {"DE:44:89:08:57:7E", "Kueche"},
  };

  void setup() override {
    // Hier können Initialisierungen erfolgen
  }

  void loop() override {
    if (bssid_sensor == nullptr) return;

    std::string bssid = bssid_sensor->state.c_str();
    std::string ap_name;

    // Überprüfen, ob die BSSID in der Tabelle existiert
    auto it = ap_map.find(bssid);
    if (it != ap_map.end()) {
      ap_name = it->second;
    } else {
      ap_name = bssid; // Unbekannte BSSID anzeigen
    }

    // Zustand nur aktualisieren, wenn sich der Name geändert hat
    if (this->state != ap_name) {
      this->publish_state(ap_name);
    }
  }
};
