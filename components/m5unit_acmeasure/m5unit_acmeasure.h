#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

#include <cinttypes>

namespace esphome {
namespace M5Unit_ACMeasure_Sensor {

static constexpr uint8_t UNIT_ACMEASURE_VOLTAGE_REG = 0x60;
static constexpr uint8_t UNIT_ACMEASURE_CURRENT_REG = 0x70;

class M5Unit_ACMeasure_Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  // void set_shunt_resistance_ohm(float shunt_resistance_ohm) { shunt_resistance_ohm_ = shunt_resistance_ohm; }
  // void set_max_voltage_v(float max_voltage_v) { max_voltage_v_ = max_voltage_v; }
  // void set_shunt_voltage_sensor(sensor::Sensor *shunt_voltage_sensor) { shunt_voltage_sensor_ = shunt_voltage_sensor; }
  // void set_power_sensor(sensor::Sensor *power_sensor) { power_sensor_ = power_sensor; }

  void set_bus_voltage_sensor(sensor::Sensor *bus_voltage_sensor) { bus_voltage_sensor_ = bus_voltage_sensor; }
  void set_max_current_a(float max_current_a) { max_current_a_ = max_current_a; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }

 protected:
  bool read_u16_(uint8_t reg, uint16_t &value);

  float max_current_a_{0.0f};
  sensor::Sensor *bus_voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};
};

}  // namespace M5Unit_ACMeasure_Sensor
}  // namespace esphome
