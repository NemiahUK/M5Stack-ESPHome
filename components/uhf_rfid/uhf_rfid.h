#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/helpers.h"  // for format_hex()

namespace esphome {
namespace uhf_rfid {

class UhfRfid : public text_sensor::TextSensor, public uart::UARTDevice, public Component {
 public:
  void set_uart_parent(uart::UARTComponent *parent) { this->set_parent(parent); }

  void setup() override {
    // nothing to do here
  }

  // Keep your original parsing logic
  int readline(int readch, unsigned char *buffer, int len) {
    const int read_timeout = 50;     // currently unused; kept for parity
    const int max_packet_size = 14;  // number of bytes

    static int pos = 0;
    static unsigned long last_read = millis();
    int rpos;

    if (pos < len - 1) {
      buffer[pos++] = static_cast<unsigned char>(readch);
      buffer[pos] = 0;
    }

    int idle = millis() - last_read;  // currently unused; kept for parity
    if (pos >= max_packet_size) {
      last_read = millis();
      rpos = pos;
      pos = 0;  // reset ready for next packet
      return rpos;
    }

    last_read = millis();
    return -1;  // still reading buffer
  }

  void loop() override {
    const int max_line_length = 80;
    static unsigned char buffer[max_line_length];

    while (this->available()) {
      int len = this->readline(this->read(), buffer, max_line_length);
      if (len > 0) {
        // format_hex(const uint8_t *data, size_t len) -> std::string
        this->publish_state(format_hex(buffer, len));
      }
    }
  }

  float get_setup_priority() const override { return setup_priority::DATA; }
};

}  // namespace uhf_rfid
}  // namespace esphome
