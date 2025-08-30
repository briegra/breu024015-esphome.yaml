#pragma once

#include "esphome.h"

class LoopTimeSensor : public PollingComponent, public Sensor {
 public:
  LoopTimeSensor(uint32_t update_interval) : PollingComponent(update_interval) {}  

  void setup() override {
    last_time_ = millis();
    loop_time_ = 0;
  }

  void loop() override {
    // Hier wird die echte Loop-Zeit berechnet
    uint32_t now = millis();
    loop_time_ = now - last_time_;
    last_time_ = now;
  }

  void update() override {
    // Wert nur alle X Sekunden veröffentlichen
    publish_state(loop_time_);
  }

 private:
  uint32_t last_time_;
  uint32_t loop_time_;
};
