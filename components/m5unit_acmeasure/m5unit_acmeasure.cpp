#include "m5unit_acmeasure.h"

#include "esphome/core/log.h"

namespace esphome {
namespace M5Unit_ACMeasure_Sensor {

static const char *const TAG = "M5Unit_ACMeasure";

bool M5Unit_ACMeasure_Component::read_u16_(uint8_t reg, uint16_t &value) {
  uint8_t data[2];
  if (!this->read_bytes(reg, data, sizeof(data))) {
    return false;
  }

  value = static_cast<uint16_t>(data[0]) | (static_cast<uint16_t>(data[1]) << 8);
  return true;
}

void M5Unit_ACMeasure_Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Unit_ACMeasure...");
}

void M5Unit_ACMeasure_Component::dump_config() {
  ESP_LOGCONFIG(TAG, "M5Unit_ACMeasure:");
  LOG_I2C_DEVICE(this);
}

float M5Unit_ACMeasure_Component::get_setup_priority() const { return setup_priority::DATA; }

void M5Unit_ACMeasure_Component::update() {
    uint16_t current_raw = 0;
    uint16_t voltage_raw = 0;
    bool ok = true;

    if (this->current_sensor_ != nullptr) {
        ok = this->read_u16_(UNIT_ACMEASURE_CURRENT_REG, current_raw) && ok;
    }

    if (this->bus_voltage_sensor_ != nullptr) {
        ok = this->read_u16_(UNIT_ACMEASURE_VOLTAGE_REG, voltage_raw) && ok;
    }

    if (!ok) {
        ESP_LOGW(TAG, "Failed to read AC measure registers");
        this->status_set_warning();
        return;
    }

  if (this->current_sensor_ != nullptr) {
        this->current_sensor_->publish_state(current_raw / 100.0f);
  }

  if (this->bus_voltage_sensor_ != nullptr) {
        this->bus_voltage_sensor_->publish_state(voltage_raw / 100.0f);
  }

  this->status_clear_warning();
}

}  // namespace M5Unit_ACMeasure_Sensor
}  // namespace esphome
