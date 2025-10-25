# components/uhf_rfid/text_sensor/__init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, text_sensor
from esphome.const import CONF_ID, CONF_UART_ID

# Import the forward-declared class from the root module
from .. import UhfRfid

AUTO_LOAD = ["uart"]

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema()
    .extend({
        cv.GenerateID(): cv.declare_id(UhfRfid),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    })
)

async def to_code(config):
    # Make sure the header is visible to the translation unit that needs the full type
    cg.add_global(cg.RawExpression('#include "esphome/components/uhf_rfid/uhf_rfid.h"'))

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)

    uart_comp = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_comp))
