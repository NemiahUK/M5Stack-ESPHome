import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, binary_sensor
from esphome.const import CONF_CHANNEL

from .. import M5Stack_ns, M5Stack_4in8out, CONF_M5Stack_4in8out_ID

DEPENDENCIES = ['m5stack_4in8out']

#MULTI_CONF = True

M5StackBinarySensor = M5Stack_ns.class_("M5Stack_4in8out_Binary_Sensor", cg.Component, i2c.I2CDevice, binary_sensor.BinarySensor)

CONF_INPUT_1 = 'input1'
CONF_INPUT_2 = 'input2'
CONF_INPUT_3 = 'input3'
CONF_INPUT_4 = 'input4'


InputBit_ = M5Stack_ns.enum("InputBit", is_class=True)

INPUT_MAP = {
    CONF_INPUT_1: InputBit_.INPUT1,
    CONF_INPUT_2: InputBit_.INPUT2,
    CONF_INPUT_3: InputBit_.INPUT3,
    CONF_INPUT_4: InputBit_.INPUT4,
}

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(M5StackBinarySensor).extend({
            cv.GenerateID(): cv.declare_id(M5StackBinarySensor),
            cv.GenerateID(CONF_M5Stack_4in8out_ID): cv.use_id(M5Stack_4in8out),
            cv.Required(CONF_CHANNEL): cv.enum(INPUT_MAP),
        }).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_M5Stack_4in8out_ID])
    
    cg.add(var.set_channel(config[CONF_CHANNEL]))