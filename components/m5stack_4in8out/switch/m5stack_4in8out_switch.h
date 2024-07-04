#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

#include "esphome/components/M5Stack_4in8out/M5Stack_4in8out.h"


namespace esphome {
namespace M5Stack_4in8out {

class M5Stack_4in8out_Switch : public Component, public switch_::Switch, public Parented<M5Stack_4in8out> {
 public:
  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  float get_setup_priority() const override;

  void setup() override;
  void dump_config() override;
  void write_state(bool state) override;

  void set_channel(OutputBit channel) { this->channel_ = (uint16_t) channel; }

  void set_interlock(const std::vector<Switch *> &interlock);
  void set_interlock_wait_time(uint32_t interlock_wait_time) { interlock_wait_time_ = interlock_wait_time; }

 protected:
  uint16_t channel_;
  std::vector<Switch *> interlock_;
  uint32_t interlock_wait_time_{0};
};

}  // namespace M5Stack_4_Relays
}  // namespace esphome
