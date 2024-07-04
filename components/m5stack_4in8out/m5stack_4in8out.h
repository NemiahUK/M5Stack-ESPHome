// START OF M5StackLib

#ifndef _MODULE_4IN8OUT_H
#define _MODULE_4IN8OUT_H

#include "Arduino.h"
#include "Wire.h"

#define MODULE_4IN8OUT_ADDR            0x45
#define MODULE_4IN8OUT_INPUT_REG       0x10
#define MODULE_4IN8OUT_OUTPUT_REG      0x20
#define MODULE_4IN8OUT_VERSION_REG     0xFE
#define MODULE_4IN8OUT_ADDR_CONFIG_REG 0xFF

class MODULE_4IN8OUT {
   private:
    uint8_t _addr = MODULE_4IN8OUT_ADDR;
    TwoWire* _wire = &Wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t sda = 21, uint8_t scl = 22,
               uint8_t addr = MODULE_4IN8OUT_ADDR);
    bool setOutput(uint8_t index, bool state);
    bool setAllOutput(bool state);
    bool reverseOutput();
    bool getInput(uint8_t index);
    bool setDeviceAddr(uint8_t addr);
    uint8_t getVersion();
};

#endif

// END OF M5StackLib



#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace M5Stack_4in8out {

enum class InputBit  : uint8_t { INPUT1 = 0, INPUT2 = 1, INPUT3 = 2, INPUT4 = 3 };

enum class OutputBit : uint8_t { OUTPUT1 = 0, OUTPUT2 = 1, OUTPUT3 = 2, OUTPUT4 = 3, OUTPUT5 = 4, OUTPUT6 = 5, OUTPUT7 = 6, OUTPUT8 = 7 };

class M5Stack_4in8out : public Component, public i2c::I2CDevice {

 public:

  void outputWrite(uint8_t number, bool state);
  bool inputRead(uint8_t number);

 protected:
  
  void dump_config() override;

  void Init(bool mode);

  void setup() override;
};

}  // namespace M5Stack_4in8out
}  // namespace esphome


