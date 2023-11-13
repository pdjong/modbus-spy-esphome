#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <map>

namespace esphome {
namespace modbus_sniffer {

#define MODBUS_SNIFFER_METER_SENSOR(name) \
 protected: \
  sensor::Sensor *name##_sensor_{nullptr}; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *(name)) { this->name##_sensor_ = name; }

#define MODBUS_SNIFFER_METER_BINARYSENSOR(name) \
 protected: \
  binary_sensor::BinarySensor *name##_binary_sensor_{nullptr}; \
\
 public: \
  void set_##name##_binary_sensor(binary_sensor::BinarySensor *(name)) { this->name##_binary_sensor_ = name; }

typedef struct {
  uint8_t address;
  uint8_t function;
  uint16_t start_address;
  uint16_t requested_registers;
} RequestMessage;

enum sensorUnit {
  temperature,
  frequency,
  pressure,
  voltage,
  current,
  onOff
};

union SensorUnion {
  sensor::Sensor *sensor;
  binary_sensor::BinarySensor *binarySensor;
};

typedef struct {
  SensorUnion sensor;
  sensorUnit unit;
} SensorAndUnit;

class ModbusSniffer : public Component, public uart::UARTDevice {
  public:  
    MODBUS_SNIFFER_METER_SENSOR(cooling_heating_temperature)
    MODBUS_SNIFFER_METER_SENSOR(sanitary_hot_water_temperature)
    MODBUS_SNIFFER_METER_SENSOR(outside_temperature)
    MODBUS_SNIFFER_METER_SENSOR(inside_temperature)
    MODBUS_SNIFFER_METER_SENSOR(heat_exchanger_water_inlet_temperature)
    MODBUS_SNIFFER_METER_SENSOR(heat_exchanger_water_outlet_temperature)
    MODBUS_SNIFFER_METER_SENSOR(compressor_working_speed_actual)
    MODBUS_SNIFFER_METER_SENSOR(compressor_working_speed_setpoint)
    MODBUS_SNIFFER_METER_SENSOR(outdoor_fan_setpoint)
    MODBUS_SNIFFER_METER_SENSOR(outdoor_fan_1_actual)
    MODBUS_SNIFFER_METER_SENSOR(indoor_coil_temperature)
    MODBUS_SNIFFER_METER_SENSOR(low_pressure)
    MODBUS_SNIFFER_METER_SENSOR(high_pressure)
    MODBUS_SNIFFER_METER_SENSOR(suction_temperature)
    MODBUS_SNIFFER_METER_SENSOR(discharge_temperature)
    MODBUS_SNIFFER_METER_SENSOR(outdoor_coil_temperature)
    MODBUS_SNIFFER_METER_SENSOR(heating_circuit_1_temperature)
    MODBUS_SNIFFER_METER_SENSOR(outdoor_voltage)
    MODBUS_SNIFFER_METER_SENSOR(outdoor_current)
    MODBUS_SNIFFER_METER_SENSOR(decode20)
    MODBUS_SNIFFER_METER_SENSOR(decode21)
    MODBUS_SNIFFER_METER_SENSOR(decode22)
    MODBUS_SNIFFER_METER_SENSOR(decode23)
    MODBUS_SNIFFER_METER_SENSOR(decode24)
    MODBUS_SNIFFER_METER_SENSOR(decode25)
    MODBUS_SNIFFER_METER_SENSOR(decode26)
    MODBUS_SNIFFER_METER_SENSOR(decode27)
    MODBUS_SNIFFER_METER_SENSOR(decode28)
    MODBUS_SNIFFER_METER_SENSOR(decode29)
    MODBUS_SNIFFER_METER_SENSOR(decode30)
    MODBUS_SNIFFER_METER_SENSOR(decode31)
    MODBUS_SNIFFER_METER_SENSOR(decode32)
    MODBUS_SNIFFER_METER_SENSOR(decode33)
    MODBUS_SNIFFER_METER_SENSOR(decode34)
    MODBUS_SNIFFER_METER_SENSOR(decode35)
    MODBUS_SNIFFER_METER_SENSOR(decode120)
    MODBUS_SNIFFER_METER_SENSOR(decode121)
    MODBUS_SNIFFER_METER_SENSOR(decode122)
    MODBUS_SNIFFER_METER_SENSOR(decode123)
    MODBUS_SNIFFER_METER_SENSOR(decode124)
    MODBUS_SNIFFER_METER_SENSOR(decode125)
    MODBUS_SNIFFER_METER_SENSOR(decode126)
    MODBUS_SNIFFER_METER_SENSOR(decode127)
    MODBUS_SNIFFER_METER_SENSOR(decode128)
    MODBUS_SNIFFER_METER_SENSOR(decode129)
    MODBUS_SNIFFER_METER_SENSOR(decode130)
    MODBUS_SNIFFER_METER_SENSOR(decode131)
    MODBUS_SNIFFER_METER_SENSOR(decode132)
    MODBUS_SNIFFER_METER_SENSOR(decode133)
    MODBUS_SNIFFER_METER_SENSOR(decode134)
    MODBUS_SNIFFER_METER_SENSOR(decode135)    
    MODBUS_SNIFFER_METER_BINARYSENSOR(pump_p1_active)
    MODBUS_SNIFFER_METER_BINARYSENSOR(pump_p2_active)
    MODBUS_SNIFFER_METER_BINARYSENSOR(heating_switch)
    MODBUS_SNIFFER_METER_BINARYSENSOR(internal_pump_active)
    MODBUS_SNIFFER_METER_BINARYSENSOR(three_way_valve)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode1)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode2)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode3)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode4)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode5)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode6)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode7)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode8)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode9)
    MODBUS_SNIFFER_METER_BINARYSENSOR(decode10)

    MODBUS_SNIFFER_METER_SENSOR(decode201)
    MODBUS_SNIFFER_METER_SENSOR(decode202)
    MODBUS_SNIFFER_METER_SENSOR(decode203)
    MODBUS_SNIFFER_METER_SENSOR(decode204)
    MODBUS_SNIFFER_METER_SENSOR(decode205)
    MODBUS_SNIFFER_METER_SENSOR(decode206)
    MODBUS_SNIFFER_METER_SENSOR(decode207)
    MODBUS_SNIFFER_METER_SENSOR(decode208)
    MODBUS_SNIFFER_METER_SENSOR(decode209)
    MODBUS_SNIFFER_METER_SENSOR(decode210)
    MODBUS_SNIFFER_METER_SENSOR(decode211)
    MODBUS_SNIFFER_METER_SENSOR(decode212)
    MODBUS_SNIFFER_METER_SENSOR(decode213)
    MODBUS_SNIFFER_METER_SENSOR(decode214)
    MODBUS_SNIFFER_METER_SENSOR(decode215)
    MODBUS_SNIFFER_METER_SENSOR(decode216)
    MODBUS_SNIFFER_METER_SENSOR(decode217)
    MODBUS_SNIFFER_METER_SENSOR(decode218)
    MODBUS_SNIFFER_METER_SENSOR(decode219)      

    MODBUS_SNIFFER_METER_SENSOR(decode301)
    MODBUS_SNIFFER_METER_SENSOR(decode302)
    MODBUS_SNIFFER_METER_SENSOR(decode303)
    MODBUS_SNIFFER_METER_SENSOR(decode304)
    MODBUS_SNIFFER_METER_SENSOR(decode305)
    MODBUS_SNIFFER_METER_SENSOR(decode306)
    MODBUS_SNIFFER_METER_SENSOR(decode307)
    MODBUS_SNIFFER_METER_SENSOR(decode308)
    MODBUS_SNIFFER_METER_SENSOR(decode309)
    MODBUS_SNIFFER_METER_SENSOR(decode310)
    MODBUS_SNIFFER_METER_SENSOR(decode311)
    MODBUS_SNIFFER_METER_SENSOR(decode312)
    MODBUS_SNIFFER_METER_SENSOR(decode313)
    MODBUS_SNIFFER_METER_SENSOR(decode314)
    MODBUS_SNIFFER_METER_SENSOR(decode315)
    MODBUS_SNIFFER_METER_SENSOR(decode316)
    MODBUS_SNIFFER_METER_SENSOR(decode317)
    MODBUS_SNIFFER_METER_SENSOR(decode318)
    MODBUS_SNIFFER_METER_SENSOR(decode319)     
    MODBUS_SNIFFER_METER_SENSOR(decode320)  

    void setup() override;
    void loop() override;
    void dump_config() override;
    float get_setup_priority() const override;

  protected:
    bool parse_modbus_byte_(uint8_t byte);
    uint32_t last_modbus_byte_{0};
    std::vector<uint8_t> rx_buffer_;
    RequestMessage last_request_message_;
    std::map<uint16_t, SensorAndUnit> registerToSensorAndUnitMap;
    
    void map_register_to_sensor_and_unit(uint16_t register, sensor::Sensor *sensor, sensorUnit unit);
    void map_register_to_sensor_and_unit(uint16_t register, binary_sensor::BinarySensor *sensor, sensorUnit unit);

    float convertRegisterValueToTemperature(uint16_t registerValue) {
      return static_cast<float>(registerValue - 3000) / 100.0f;
    }

    float convertRegisterValueToFloat(uint16_t registerValue) {
      return static_cast<float>(registerValue);
    }

    bool convertRegisterValueToOnOff(uint16_t registerValue) {
      return static_cast<bool>(registerValue);
    }

    void fleppertje();
    void log_rx_buffer();
    
  public:
    static void read_loop_task(void* params);
};

typedef float(ModbusSniffer::*RegisterValueConversion)(uint16_t);

} //namespace modbus_sniffer
} //namespace esphome