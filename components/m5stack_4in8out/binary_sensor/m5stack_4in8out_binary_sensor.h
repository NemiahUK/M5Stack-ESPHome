#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#include "esphome/components/M5Stack_4in8out/M5Stack_4in8out.h"


namespace esphome {
namespace M5Stack_4in8out {

class M5Stack_4in8out_Binary_Sensor : public binary_sensor::BinarySensor, public PollingComponent, public Parented<M5Stack_4in8out> {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  bool process();

  void set_channel(InputBit channel) { this->channel_ = (uint16_t) channel; }

  protected:
    uint16_t channel_;
};

} //namespace M5Stack_4in8out_Binary_Switch
} //namespace esphome