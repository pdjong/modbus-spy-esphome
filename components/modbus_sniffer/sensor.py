import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.components import binary_sensor
from esphome.components import uart
from esphome.const import  (
    CONF_ID, 
    DEVICE_CLASS_FREQUENCY,
    DEVICE_CLASS_TEMPERATURE,
    ICON_THERMOMETER,
    ICON_CURRENT_AC,
    ICON_FLASH,
    UNIT_CELSIUS, 
    UNIT_HERTZ,
    UNIT_VOLT,
    UNIT_AMPERE,
    STATE_CLASS_MEASUREMENT,
)

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["binary_sensor"]

modbus_sniffer_ns = cg.esphome_ns.namespace("modbus_sniffer")
modbus_sniffer = modbus_sniffer_ns.class_("ModbusSniffer", cg.Component, uart.UARTDevice)
binary_sensor_ns = cg.esphome_ns.namespace("binary_sensor")

CONF_COOLING_HEATING_TEMPERATURE = "cooling_heating_temperature"
CONF_SANITARY_HOT_WATER_TEMPERATURE = "sanitary_hot_water_temperature"
CONF_OUTSIDE_TEMPERATURE = "outside_temperature"
CONF_INSIDE_TEMPERATURE = "inside_temperature"
CONF_HEAT_EXCHANGER_WATER_OUTLET_TEMPERATURE = "heat_exchanger_water_outlet_temperature"
CONF_HEAT_EXCHANGER_WATER_INLET_TEMPERATURE = "heat_exchanger_water_inlet_temperature"
CONF_COMPRESSOR_WORKING_SPEED_ACTUAL = "compressor_working_speed_actual"
CONF_COMPRESSOR_WORKING_SPEED_SETPOINT = "compressor_working_speed_setpoint"
CONF_OUTDOOR_FAN_SETPOINT = "outdoor_fan_setpoint"
CONF_OUTDOOR_FAN_1_ACTUAL = "outdoor_fan_1_actual"
CONF_INDOOR_COIL_TEMPERATURE = "indoor_coil_temperature"
CONF_LOW_PRESSURE = "low_pressure"
CONF_HIGH_PRESSURE = "high_pressure"
CONF_SUCTION_TEMPERATURE = "suction_temperature"
CONF_DISCHARGE_TEMPERATURE = "discharge_temperature"
CONF_OUTDOOR_COIL_TEMPERATURE = "outdoor_coil_temperature"
CONF_INTERNAL_PUMP_ACTIVE = "internal_pump_active"
CONF_HEATING_CIRCUIT_1_TEMPERATURE = "heating_circuit_1_temperature"
CONF_PUMP_P1_ACTIVE = "pump_p1_active"
CONF_PUMP_P2_ACTIVE = "pump_p2_active"
CONF_HEATING_SWITCH = "heating_switch"
CONF_THREE_WAY_VALVE = "three_way_valve"
CONF_OUTDOOR_VOLTAGE = "outdoor_voltage"
CONF_OUTDOOR_CURRENT = "outdoor_current"
CONF_DECODE1 = "decode1"
CONF_DECODE2 = "decode2"
CONF_DECODE3 = "decode3"
CONF_DECODE4 = "decode4"
CONF_DECODE5 = "decode5"
CONF_DECODE6 = "decode6"
CONF_DECODE7 = "decode7"
CONF_DECODE8 = "decode8"
CONF_DECODE9 = "decode9"
CONF_DECODE10 = "decode10"
CONF_DECODE20 = "decode20"
CONF_DECODE21 = "decode21"
CONF_DECODE22 = "decode22"
CONF_DECODE23 = "decode23"
CONF_DECODE24 = "decode24"
CONF_DECODE25 = "decode25"
CONF_DECODE26 = "decode26"
CONF_DECODE27 = "decode27"
CONF_DECODE28 = "decode28"
CONF_DECODE29 = "decode29"
CONF_DECODE30 = "decode30"
CONF_DECODE31 = "decode31"
CONF_DECODE32 = "decode32"
CONF_DECODE33 = "decode33"
CONF_DECODE34 = "decode34"
CONF_DECODE35 = "decode35"
CONF_DECODE120 = "decode120"
CONF_DECODE121 = "decode121"
CONF_DECODE122 = "decode122"
CONF_DECODE123 = "decode123"
CONF_DECODE124 = "decode124"
CONF_DECODE125 = "decode125"
CONF_DECODE126 = "decode126"
CONF_DECODE127 = "decode127"
CONF_DECODE128 = "decode128"
CONF_DECODE129 = "decode129"
CONF_DECODE130 = "decode130"
CONF_DECODE131 = "decode131"
CONF_DECODE132 = "decode132"
CONF_DECODE133 = "decode133"
CONF_DECODE134 = "decode134"
CONF_DECODE135 = "decode135"

CONF_DECODE201 = "decode201"
CONF_DECODE202 = "decode202"
CONF_DECODE203 = "decode203"
CONF_DECODE204 = "decode204"
CONF_DECODE205 = "decode205"
CONF_DECODE206 = "decode206"
CONF_DECODE207 = "decode207"
CONF_DECODE208 = "decode208"
CONF_DECODE209 = "decode209"
CONF_DECODE210 = "decode210"
CONF_DECODE211 = "decode211"
CONF_DECODE212 = "decode212"
CONF_DECODE213 = "decode213"
CONF_DECODE214 = "decode214"
CONF_DECODE215 = "decode215"
CONF_DECODE216 = "decode216"
CONF_DECODE217 = "decode217"
CONF_DECODE218 = "decode218"
CONF_DECODE219 = "decode219"

CONF_DECODE301 = "decode301"
CONF_DECODE302 = "decode302"
CONF_DECODE303 = "decode303"
CONF_DECODE304 = "decode304"
CONF_DECODE305 = "decode305"
CONF_DECODE306 = "decode306"
CONF_DECODE307 = "decode307"
CONF_DECODE308 = "decode308"
CONF_DECODE309 = "decode309"
CONF_DECODE310 = "decode310"
CONF_DECODE311 = "decode311"
CONF_DECODE312 = "decode312"
CONF_DECODE313 = "decode313"
CONF_DECODE314 = "decode314"
CONF_DECODE315 = "decode315"
CONF_DECODE316 = "decode316"
CONF_DECODE317 = "decode317"
CONF_DECODE318 = "decode318"
CONF_DECODE319 = "decode319"
CONF_DECODE320 = "decode320"


DEVICE_CLASS_PRESSURE = "pressure"
DEVICE_CLASS_VOLTAGE = "voltage"
DEVICE_CLASS_CURRENT = "current"

UNIT_BAR = "bar"
UNIT_RPM = "rpm"

ICON_FAN = "mdi:fan"

SENSORS = {
    CONF_HEAT_EXCHANGER_WATER_OUTLET_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_HEAT_EXCHANGER_WATER_INLET_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_COMPRESSOR_WORKING_SPEED_ACTUAL: sensor.sensor_schema(
        unit_of_measurement=UNIT_HERTZ,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_FREQUENCY,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FAN
    ),
    CONF_COMPRESSOR_WORKING_SPEED_SETPOINT: sensor.sensor_schema(
        unit_of_measurement=UNIT_HERTZ,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_FREQUENCY,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FAN
    ),
    CONF_OUTDOOR_FAN_SETPOINT: sensor.sensor_schema(
        unit_of_measurement=UNIT_RPM,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_FREQUENCY,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FAN
    ),
    CONF_OUTDOOR_FAN_1_ACTUAL: sensor.sensor_schema(
        unit_of_measurement=UNIT_RPM,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_FREQUENCY,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FAN
    ),
    CONF_OUTSIDE_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_INSIDE_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    )    ,
    CONF_COOLING_HEATING_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_SANITARY_HOT_WATER_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_INDOOR_COIL_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_LOW_PRESSURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_BAR,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_PRESSURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_HIGH_PRESSURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_BAR,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_PRESSURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_SUCTION_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_DISCHARGE_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_OUTDOOR_COIL_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),   
    CONF_HEATING_CIRCUIT_1_TEMPERATURE: sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_THERMOMETER
    ),
    CONF_OUTDOOR_VOLTAGE: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_FLASH
    ),
    CONF_OUTDOOR_CURRENT: sensor.sensor_schema(
        unit_of_measurement=UNIT_AMPERE,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_CURRENT,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_CURRENT_AC
    ),
    CONF_DECODE20: sensor.sensor_schema(),  
    CONF_DECODE21: sensor.sensor_schema(),  
    CONF_DECODE22: sensor.sensor_schema(),  
    CONF_DECODE23: sensor.sensor_schema(),  
    CONF_DECODE24: sensor.sensor_schema(),  
    CONF_DECODE25: sensor.sensor_schema(),  
    CONF_DECODE26: sensor.sensor_schema(),  
    CONF_DECODE27: sensor.sensor_schema(),  
    CONF_DECODE28: sensor.sensor_schema(),  
    CONF_DECODE29: sensor.sensor_schema(),  
    CONF_DECODE30: sensor.sensor_schema(),  
    CONF_DECODE31: sensor.sensor_schema(),  
    CONF_DECODE32: sensor.sensor_schema(),  
    CONF_DECODE33: sensor.sensor_schema(),  
    CONF_DECODE34: sensor.sensor_schema(),  
    CONF_DECODE35: sensor.sensor_schema(),
    CONF_DECODE120: sensor.sensor_schema(),  
    CONF_DECODE121: sensor.sensor_schema(),  
    CONF_DECODE122: sensor.sensor_schema(),  
    CONF_DECODE123: sensor.sensor_schema(),  
    CONF_DECODE124: sensor.sensor_schema(),  
    CONF_DECODE125: sensor.sensor_schema(),  
    CONF_DECODE126: sensor.sensor_schema(),  
    CONF_DECODE127: sensor.sensor_schema(),  
    CONF_DECODE128: sensor.sensor_schema(),  
    CONF_DECODE129: sensor.sensor_schema(),  
    CONF_DECODE130: sensor.sensor_schema(),  
    CONF_DECODE131: sensor.sensor_schema(),  
    CONF_DECODE132: sensor.sensor_schema(),  
    CONF_DECODE133: sensor.sensor_schema(),  
    CONF_DECODE134: sensor.sensor_schema(),  
    CONF_DECODE135: sensor.sensor_schema(),
    CONF_DECODE201: sensor.sensor_schema(),  
    CONF_DECODE202: sensor.sensor_schema(),  
    CONF_DECODE203: sensor.sensor_schema(),  
    CONF_DECODE204: sensor.sensor_schema(),  
    CONF_DECODE205: sensor.sensor_schema(),  
    CONF_DECODE206: sensor.sensor_schema(),  
    CONF_DECODE207: sensor.sensor_schema(),  
    CONF_DECODE208: sensor.sensor_schema(),  
    CONF_DECODE209: sensor.sensor_schema(),  
    CONF_DECODE210: sensor.sensor_schema(),  
    CONF_DECODE211: sensor.sensor_schema(),  
    CONF_DECODE212: sensor.sensor_schema(),  
    CONF_DECODE213: sensor.sensor_schema(),  
    CONF_DECODE214: sensor.sensor_schema(),  
    CONF_DECODE215: sensor.sensor_schema(),
    CONF_DECODE216: sensor.sensor_schema(),  
    CONF_DECODE217: sensor.sensor_schema(),  
    CONF_DECODE218: sensor.sensor_schema(),  
    CONF_DECODE219: sensor.sensor_schema(),
    CONF_DECODE301: sensor.sensor_schema(),  
    CONF_DECODE302: sensor.sensor_schema(),  
    CONF_DECODE303: sensor.sensor_schema(),  
    CONF_DECODE304: sensor.sensor_schema(),  
    CONF_DECODE305: sensor.sensor_schema(),  
    CONF_DECODE306: sensor.sensor_schema(),  
    CONF_DECODE307: sensor.sensor_schema(),  
    CONF_DECODE308: sensor.sensor_schema(),  
    CONF_DECODE309: sensor.sensor_schema(),  
    CONF_DECODE310: sensor.sensor_schema(),  
    CONF_DECODE311: sensor.sensor_schema(),  
    CONF_DECODE312: sensor.sensor_schema(),  
    CONF_DECODE313: sensor.sensor_schema(),  
    CONF_DECODE314: sensor.sensor_schema(),  
    CONF_DECODE315: sensor.sensor_schema(),
    CONF_DECODE316: sensor.sensor_schema(),  
    CONF_DECODE317: sensor.sensor_schema(),  
    CONF_DECODE318: sensor.sensor_schema(),  
    CONF_DECODE319: sensor.sensor_schema(),
    CONF_DECODE320: sensor.sensor_schema()
}

BINARY_SENSORS = {
    CONF_PUMP_P1_ACTIVE: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_PUMP_P2_ACTIVE: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_INTERNAL_PUMP_ACTIVE: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_HEATING_SWITCH: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_THREE_WAY_VALVE: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE1: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE2: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE3: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE4: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE5: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE6: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE7: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE8: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE9: binary_sensor.BINARY_SENSOR_SCHEMA,
    CONF_DECODE10: binary_sensor.BINARY_SENSOR_SCHEMA,
}

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(modbus_sniffer)
        }
    )
    .extend(
        {
            cv.Optional(sensor_name): schema for sensor_name, schema in SENSORS.items()
        }
    )    .extend(
        {
            cv.Optional(sensor_name): schema for sensor_name, schema in BINARY_SENSORS.items()
        }
    ).extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    cg.add_global(modbus_sniffer_ns.using)
    cg.add_global(binary_sensor_ns.using)
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for name in SENSORS:
        if name in config:
            sens = await sensor.new_sensor(config[name])
            cg.add(getattr(var, f"set_{name}_sensor")(sens))

    for name in BINARY_SENSORS:
        if name in config:
            sens = await binary_sensor.new_binary_sensor(config[name])
            cg.add(getattr(var, f"set_{name}_binary_sensor")(sens))
