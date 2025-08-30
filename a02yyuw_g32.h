#include "esphome.h"

class A02YYUW : public PollingComponent, public UARTDevice {
 public:
  Sensor *distance_sensor = new Sensor();

  // Konstruktor mit dynamischem Polling-Intervall
  explicit A02YYUW(UARTComponent *uart, uint32_t update_interval)
      : PollingComponent(update_interval), UARTDevice(uart) {}

  void setup() override {
    // Setup abgeschlossen
  }

  void update() override {
    // Sende-Befehl an den Sensor, um eine Messung zu starten
    write(0xFF);
    flush();

    // Empfangspuffer lesen
    uint8_t buffer[4];
    int bytes_read = 0;

    while (available() && bytes_read < 4) {
      buffer[bytes_read] = read();
      bytes_read++;
    }

    if (bytes_read == 4) {
      // Daten validieren
      if (buffer[0] == 0xFF) {  // Startbyte prüfen
        uint16_t distance = (buffer[1] << 8) | buffer[2];  // Distanz berechnen
        uint8_t checksum = (buffer[0] + buffer[1] + buffer[2]) & 0xFF;

        if (checksum == buffer[3]) {  // Prüfsumme validieren
          float distance_cm = distance / 10.0;  // Umwandlung in cm
          distance_sensor->publish_state(distance_cm);
        }
      }
    }
  }
};
