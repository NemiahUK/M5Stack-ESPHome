#include "esphome/core/log.h"
#include "m5stack_4in8out_binary_sensor.h"

namespace esphome {
namespace M5Stack_4in8out {

static const char *TAG = "binary_sensor.M5Stack_4in8out";

void M5Stack_4in8out_Binary_Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Stack_4in8out binarySensor '%s'...", this->name_.c_str());
}

void M5Stack_4in8out_Binary_Sensor::update() {
  this->process();
}
  
bool M5Stack_4in8out_Binary_Sensor::process() {
  // OUTPUT MUST BE INVERTED AT THE READ LEVEL TO AVOID CONFUSION
  bool input_state = !this->parent_->inputRead(this->channel_);
  this->publish_state(input_state);
  return input_state;
} 

void M5Stack_4in8out_Binary_Sensor::dump_config() {
    ESP_LOGCONFIG(TAG, "Custom binary sensor");
}

} //namespace empty_binary_sensor
} //namespace esphome