#ifndef MODBUS_REGISTER_SENSOR_H_
#define MODBUS_REGISTER_SENSOR_H_

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST

namespace esphome {
namespace modbus_spy {

// static const char *TAG = "ModbusRegisterSensor";

class IModbusRegisterSensor {
 public:
  virtual void publish_state(uint16_t state) = 0;
};

#ifndef UNIT_TEST

class ModbusRegisterSensor : public IModbusRegisterSensor {
 public:
  virtual void publish_state(uint16_t state) {
    ESP_LOGI("ModbusRegisterSensor", "About to publish state: %d", state);
    this->sensor_->publish_state(static_cast<float>(state));
  }
  sensor::Sensor* get_sensor() const { return this->sensor_; }

 protected:
  sensor::Sensor* sensor_;
};

#endif // UNIT_TEST

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_REGISTER_SENSOR_H_