#ifndef __UNIT_ACMEASURE_H
#define __UNIT_ACMEASURE_H

#include "Arduino.h"
#include "Wire.h"

#define UNIT_ACMEASURE_ADDR                      0x42
#define UNIT_ACMEASURE_VOLTAGE_STRING_REG        0x00
#define UNIT_ACMEASURE_CURRENT_STRING_REG        0x10
#define UNIT_ACMEASURE_POWER_STRING_REG          0x20
#define UNIT_ACMEASURE_APPARENT_POWER_STRING_REG 0x30
#define UNIT_ACMEASURE_POWER_FACTOR_STRING_REG   0x40
#define UNIT_ACMEASURE_KWH_STRING_REG            0x50
#define UNIT_ACMEASURE_VOLTAGE_REG               0x60
#define UNIT_ACMEASURE_CURRENT_REG               0x70
#define UNIT_ACMEASURE_POWER_REG                 0x80
#define UNIT_ACMEASURE_APPARENT_POWER_REG        0x90
#define UNIT_ACMEASURE_POWER_FACTOR_REG          0xA0
#define UNIT_ACMEASURE_KWH_REG                   0xB0
#define UNIT_ACMEASURE_VOLTAGE_FACTOR_REG        0xC0
#define UNIT_ACMEASURE_CURRENT_FACTOR_REG        0xD0
#define UNIT_ACMEASURE_SAVE_FACTOR_REG           0xE0
#define UNIT_ACMEASURE_GET_READY_REG             0xFC
#define JUMP_TO_BOOTLOADER_REG                   0xFD
#define FIRMWARE_VERSION_REG                     0xFE
#define I2C_ADDRESS_REG                          0xFF

class UNIT_ACMEASURE {
   private:
    uint8_t _addr = UNIT_ACMEASURE_ADDR;
    TwoWire* _wire = &Wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed = 100000L;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t addr = UNIT_ACMEASURE_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    uint8_t getFirmwareVersion(void);
    uint16_t getVoltage(void);
    uint16_t getCurrent(void);
    uint32_t getPower(void);
    uint32_t getApparentPower(void);
    uint8_t getPowerFactor(void);
    uint32_t getKWH(void);
    void getVoltageString(char *str);
    void getCurrentString(char *str);
    void getPowerString(char *str);
    void getApparentPowerString(char *str);
    void getPowerFactorString(char *str);
    void getKWH(char *str);
    uint8_t getReady(void);
    void setKWH(uint32_t value);
    uint8_t getVoltageFactor(void);
    uint8_t getCurrentFactor(void);
    void setVoltageFactor(uint8_t value);
    void setCurrentFactor(uint8_t value);
    void saveVoltageCurrentFactor(void);
    void jumpBootloader(void);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
};

#endif








#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

#include <cinttypes>

namespace esphome {
namespace M5Unit_ACMeasure_Sensor {

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
  float max_current_a_;
  sensor::Sensor *bus_voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};

  // float shunt_resistance_ohm_;
  // float max_voltage_v_;
  // uint32_t calibration_lsb_;
  // sensor::Sensor *shunt_voltage_sensor_{nullptr};
  // sensor::Sensor *power_sensor_{nullptr};
  
};

}  // namespace ina219
}  // namespace esphome
