import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, switch
from esphome.const import CONF_CHANNEL

from .. import M5Stack_ns, M5Stack_4in8out, CONF_M5Stack_4in8out_ID

DEPENDENCIES = ['m5stack_4in8out']

#MULTI_CONF = True

M5StackSwitch = M5Stack_ns.class_("M5Stack_4in8out_Switch", cg.Component, i2c.I2CDevice, switch.Switch)

CONF_INTERLOCK_WAIT_TIME = "interlock_wait_time"

CONF_OUTPUT_1 = 'output1'
CONF_OUTPUT_2 = 'output2'
CONF_OUTPUT_3 = 'output3'
CONF_OUTPUT_4 = 'output4'
CONF_OUTPUT_5 = 'output5'
CONF_OUTPUT_6 = 'output6'
CONF_OUTPUT_7 = 'output7'
CONF_OUTPUT_8 = 'output8'

OutputBit_ = M5Stack_ns.enum("OutputBit", is_class=True)

SWITCH_MAP = {
    CONF_OUTPUT_1: OutputBit_.OUTPUT1,
    CONF_OUTPUT_2: OutputBit_.OUTPUT2,
    CONF_OUTPUT_3: OutputBit_.OUTPUT3,
    CONF_OUTPUT_4: OutputBit_.OUTPUT4,
    CONF_OUTPUT_5: OutputBit_.OUTPUT5,
    CONF_OUTPUT_6: OutputBit_.OUTPUT6,
    CONF_OUTPUT_7: OutputBit_.OUTPUT7,
    CONF_OUTPUT_8: OutputBit_.OUTPUT8,
}

CONFIG_SCHEMA = switch.switch_schema(M5StackSwitch).extend({
            cv.GenerateID(): cv.declare_id(M5StackSwitch),
            cv.GenerateID(CONF_M5Stack_4in8out_ID): cv.use_id(M5Stack_4in8out),
            cv.Required(CONF_CHANNEL): cv.enum(SWITCH_MAP),
        }).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_M5Stack_4in8out_ID])
    
    cg.add(var.set_channel(config[CONF_CHANNEL]))