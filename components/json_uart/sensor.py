import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor as sensor_component, uart
from esphome.const import UNIT_EMPTY, ICON_EMPTY

json_uart_ns = cg.esphome_ns.namespace("json_uart")

JsonUartSensor = json_uart_ns.class_("JsonUartSensor", sensor_component.Sensor, cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = sensor_component.sensor_schema(
    JsonUartSensor, unit_of_measurement=cv.string, icon=ICON_EMPTY, accuracy_decimals=1
).extend({
    cv.Required("key"): cv.string,
}).extend(cv.polling_component_schema("10s")).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = await sensor_component.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    cg.add(var.set_key(config["key"]))
    cg.add(var.set_unit_of_measurement(config["unit_of_measurement"]))
