import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ["@Alexander Harris"]
DEPENDENCIES = ['i2c']

MULTI_CONF = True

CONF_I2C_ADDR = 0X45

CONF_M5Stack_4in8out_ID = "M5Stack_4in8out_id"

M5Stack_ns = cg.esphome_ns.namespace("M5Stack_4in8out")
M5Stack_4in8out = M5Stack_ns.class_("M5Stack_4in8out",  cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (cv.Schema({
            cv.GenerateID(): cv.declare_id(M5Stack_4in8out),
        })
        .extend(cv.COMPONENT_SCHEMA)
        .extend(i2c.i2c_device_schema(CONF_I2C_ADDR)))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)