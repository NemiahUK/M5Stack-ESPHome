import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, text_sensor
from esphome.const import CONF_ID, CONF_UART_ID

AUTO_LOAD = ["uart", "text_sensor"]

uhf_ns = cg.esphome_ns.namespace("uhf_rfid")
UhfRfid = uhf_ns.class_("UhfRfid", text_sensor.TextSensor, uart.UARTDevice, cg.Component)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema()
    .extend({
        cv.GenerateID(): cv.declare_id(UhfRfid),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    })
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    uart_comp = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_comp))
