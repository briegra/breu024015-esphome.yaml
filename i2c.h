#include <Wire.h>
#include "esphome.h"

uint16_t read_register(uint8_t reg) {
  uint16_t value = 0;  // Standardwert, der immer zur�ckgegeben wird
  Wire.beginTransmission(0x40);  // INA219 I�C-Adresse (Standard)
  if (Wire.write(reg) != 1) {
    ESP_LOGW("custom", "Fehler: Schreiben an Register 0x%02X fehlgeschlagen", reg);
    return value;  // R�ckgabe von Standardwert
  }
  if (Wire.endTransmission() != 0) {
    ESP_LOGW("custom", "Fehler: Keine Verbindung zum INA219 bei Register 0x%02X", reg);
    return value;  // R�ckgabe von Standardwert
  }
  Wire.requestFrom(0x40, 2);
  if (Wire.available() == 2) {
    value = (Wire.read() << 8) | Wire.read();
  } else {
    ESP_LOGW("custom", "Fehler: Register 0x%02X konnte nicht vollst�ndig gelesen werden", reg);
  }
  return value;  // Immer einen Wert zur�ckgeben
}


void calibrate_ina219() {
  Wire.beginTransmission(0x40);  // INA219 I�C-Adresse
  Wire.write(0x05);  // Kalibrierungsregister (CALIBRATION)
  Wire.write(0x00);  // Wert f�r die obere Byte
  Wire.write(0xA0);  // Wert f�r die untere Byte (angepasst f�r 0,1 Ohm Shunt)
  Wire.endTransmission();
}

