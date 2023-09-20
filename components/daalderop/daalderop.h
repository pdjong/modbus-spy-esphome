#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <map>

namespace esphome {
namespace daalderop {

#define DAALDEROP_METER_SENSOR(name) \
 protected: \
  sensor::Sensor *name##_sensor_{nullptr}; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *(name)) { this->name##_sensor_ = name; }

#define DAALDEROP_METER_BINARYSENSOR(name) \
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

class Daalderop : public Component, public uart::UARTDevice {
  public:  
    DAALDEROP_METER_SENSOR(cooling_heating_temperature)
    DAALDEROP_METER_SENSOR(sanitary_hot_water_temperature)
    DAALDEROP_METER_SENSOR(outside_temperature)
    DAALDEROP_METER_SENSOR(inside_temperature)
    DAALDEROP_METER_SENSOR(heat_exchanger_water_inlet_temperature)
    DAALDEROP_METER_SENSOR(heat_exchanger_water_outlet_temperature)
    DAALDEROP_METER_SENSOR(compressor_working_speed_actual)
    DAALDEROP_METER_SENSOR(compressor_working_speed_setpoint)
    DAALDEROP_METER_SENSOR(outdoor_fan_setpoint)
    DAALDEROP_METER_SENSOR(outdoor_fan_1_actual)
    DAALDEROP_METER_SENSOR(indoor_coil_temperature)
    DAALDEROP_METER_SENSOR(low_pressure)
    DAALDEROP_METER_SENSOR(high_pressure)
    DAALDEROP_METER_SENSOR(suction_temperature)
    DAALDEROP_METER_SENSOR(discharge_temperature)
    DAALDEROP_METER_SENSOR(outdoor_coil_temperature)
    DAALDEROP_METER_SENSOR(heating_circuit_1_temperature)
    DAALDEROP_METER_SENSOR(outdoor_voltage)
    DAALDEROP_METER_SENSOR(outdoor_current)
    DAALDEROP_METER_SENSOR(decode20)
    DAALDEROP_METER_SENSOR(decode21)
    DAALDEROP_METER_SENSOR(decode22)
    DAALDEROP_METER_SENSOR(decode23)
    DAALDEROP_METER_SENSOR(decode24)
    DAALDEROP_METER_SENSOR(decode25)
    DAALDEROP_METER_SENSOR(decode26)
    DAALDEROP_METER_SENSOR(decode27)
    DAALDEROP_METER_SENSOR(decode28)
    DAALDEROP_METER_SENSOR(decode29)
    DAALDEROP_METER_SENSOR(decode30)
    DAALDEROP_METER_SENSOR(decode31)
    DAALDEROP_METER_SENSOR(decode32)
    DAALDEROP_METER_SENSOR(decode33)
    DAALDEROP_METER_SENSOR(decode34)
    DAALDEROP_METER_SENSOR(decode35)
    DAALDEROP_METER_SENSOR(decode120)
    DAALDEROP_METER_SENSOR(decode121)
    DAALDEROP_METER_SENSOR(decode122)
    DAALDEROP_METER_SENSOR(decode123)
    DAALDEROP_METER_SENSOR(decode124)
    DAALDEROP_METER_SENSOR(decode125)
    DAALDEROP_METER_SENSOR(decode126)
    DAALDEROP_METER_SENSOR(decode127)
    DAALDEROP_METER_SENSOR(decode128)
    DAALDEROP_METER_SENSOR(decode129)
    DAALDEROP_METER_SENSOR(decode130)
    DAALDEROP_METER_SENSOR(decode131)
    DAALDEROP_METER_SENSOR(decode132)
    DAALDEROP_METER_SENSOR(decode133)
    DAALDEROP_METER_SENSOR(decode134)
    DAALDEROP_METER_SENSOR(decode135)    
    DAALDEROP_METER_BINARYSENSOR(pump_p1_active)
    DAALDEROP_METER_BINARYSENSOR(pump_p2_active)
    DAALDEROP_METER_BINARYSENSOR(heating_switch)
    DAALDEROP_METER_BINARYSENSOR(internal_pump_active)
    DAALDEROP_METER_BINARYSENSOR(three_way_valve)
    DAALDEROP_METER_BINARYSENSOR(decode1)
    DAALDEROP_METER_BINARYSENSOR(decode2)
    DAALDEROP_METER_BINARYSENSOR(decode3)
    DAALDEROP_METER_BINARYSENSOR(decode4)
    DAALDEROP_METER_BINARYSENSOR(decode5)
    DAALDEROP_METER_BINARYSENSOR(decode6)
    DAALDEROP_METER_BINARYSENSOR(decode7)
    DAALDEROP_METER_BINARYSENSOR(decode8)
    DAALDEROP_METER_BINARYSENSOR(decode9)
    DAALDEROP_METER_BINARYSENSOR(decode10)

    DAALDEROP_METER_SENSOR(decode201)
    DAALDEROP_METER_SENSOR(decode202)
    DAALDEROP_METER_SENSOR(decode203)
    DAALDEROP_METER_SENSOR(decode204)
    DAALDEROP_METER_SENSOR(decode205)
    DAALDEROP_METER_SENSOR(decode206)
    DAALDEROP_METER_SENSOR(decode207)
    DAALDEROP_METER_SENSOR(decode208)
    DAALDEROP_METER_SENSOR(decode209)
    DAALDEROP_METER_SENSOR(decode210)
    DAALDEROP_METER_SENSOR(decode211)
    DAALDEROP_METER_SENSOR(decode212)
    DAALDEROP_METER_SENSOR(decode213)
    DAALDEROP_METER_SENSOR(decode214)
    DAALDEROP_METER_SENSOR(decode215)
    DAALDEROP_METER_SENSOR(decode216)
    DAALDEROP_METER_SENSOR(decode217)
    DAALDEROP_METER_SENSOR(decode218)
    DAALDEROP_METER_SENSOR(decode219)      

    DAALDEROP_METER_SENSOR(decode301)
    DAALDEROP_METER_SENSOR(decode302)
    DAALDEROP_METER_SENSOR(decode303)
    DAALDEROP_METER_SENSOR(decode304)
    DAALDEROP_METER_SENSOR(decode305)
    DAALDEROP_METER_SENSOR(decode306)
    DAALDEROP_METER_SENSOR(decode307)
    DAALDEROP_METER_SENSOR(decode308)
    DAALDEROP_METER_SENSOR(decode309)
    DAALDEROP_METER_SENSOR(decode310)
    DAALDEROP_METER_SENSOR(decode311)
    DAALDEROP_METER_SENSOR(decode312)
    DAALDEROP_METER_SENSOR(decode313)
    DAALDEROP_METER_SENSOR(decode314)
    DAALDEROP_METER_SENSOR(decode315)
    DAALDEROP_METER_SENSOR(decode316)
    DAALDEROP_METER_SENSOR(decode317)
    DAALDEROP_METER_SENSOR(decode318)
    DAALDEROP_METER_SENSOR(decode319)     
    DAALDEROP_METER_SENSOR(decode320)  

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
    
  public:
    static void read_loop_task(void* params);
};

typedef float(Daalderop::*RegisterValueConversion)(uint16_t);

} //namespace daalderop
} //namespace esphome