import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_CURRENT,
    CONF_ID,
    STATE_CLASS_MEASUREMENT,

    CONF_MAX_CURRENT,
    DEVICE_CLASS_CURRENT,
    UNIT_AMPERE,

    CONF_BUS_VOLTAGE,
    UNIT_VOLT,
    DEVICE_CLASS_VOLTAGE,

    # CONF_MAX_VOLTAGE,
    # CONF_POWER,
    # CONF_SHUNT_RESISTANCE,
    # CONF_SHUNT_VOLTAGE,
    # DEVICE_CLASS_POWER,
    # UNIT_WATT,
)

DEPENDENCIES = ["i2c"]

MULTI_CONF = True

CONF_I2C_ADDR = 0X42

M5Unit_ACMeasure_Sensor_ns = cg.esphome_ns.namespace("M5Unit_ACMeasure_Sensor")
M5Unit_ACMeasure_Component = M5Unit_ACMeasure_Sensor_ns.class_(
    "M5Unit_ACMeasure_Component", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(M5Unit_ACMeasure_Component),
            cv.Optional(CONF_CURRENT): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                accuracy_decimals=3,
                device_class=DEVICE_CLASS_CURRENT,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_MAX_CURRENT, default=10): cv.All(
                cv.current, cv.Range(min=0.0)
            ),
            cv.Optional(CONF_BUS_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            # cv.Optional(CONF_SHUNT_VOLTAGE): sensor.sensor_schema(
            #     unit_of_measurement=UNIT_VOLT,
            #     accuracy_decimals=2,
            #     device_class=DEVICE_CLASS_VOLTAGE,
            #     state_class=STATE_CLASS_MEASUREMENT,
            # ),
            # cv.Optional(CONF_POWER): sensor.sensor_schema(
            #     unit_of_measurement=UNIT_WATT,
            #     accuracy_decimals=2,
            #     device_class=DEVICE_CLASS_POWER,
            #     state_class=STATE_CLASS_MEASUREMENT,
            # ),
            # cv.Optional(CONF_SHUNT_RESISTANCE, default=0.1): cv.All(
            #     cv.resistance, cv.Range(min=0.0, max=32.0)
            # ),
            # cv.Optional(CONF_MAX_VOLTAGE, default=32.0): cv.All(
            #     cv.voltage, cv.Range(min=0.0, max=32.0)
            # ),
        }
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(CONF_I2C_ADDR))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_max_current_a(config[CONF_MAX_CURRENT]))

    if CONF_CURRENT in config:
        sens = await sensor.new_sensor(config[CONF_CURRENT])
        cg.add(var.set_current_sensor(sens))

    if CONF_BUS_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_BUS_VOLTAGE])
        cg.add(var.set_bus_voltage_sensor(sens))

    # cg.add(var.set_shunt_resistance_ohm(config[CONF_SHUNT_RESISTANCE]))
    # cg.add(var.set_max_voltage_v(config[CONF_MAX_VOLTAGE]))

    # if CONF_SHUNT_VOLTAGE in config:
    #     sens = await sensor.new_sensor(config[CONF_SHUNT_VOLTAGE])
    #     cg.add(var.set_shunt_voltage_sensor(sens))

    # if CONF_POWER in config:
    #     sens = await sensor.new_sensor(config[CONF_POWER])
    #     cg.add(var.set_power_sensor(sens))
