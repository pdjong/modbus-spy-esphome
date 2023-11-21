#ifndef MODBUS_REGISTER_SENSOR_H_
#define MODBUS_REGISTER_SENSOR_H_

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#endif // UNIT_TEST

namespace esphome {
namespace modbus_spy {

class IModbusRegisterSensor {
 public:
  virtual void publish_state(uint16_t state) = 0;
};

#ifndef UNIT_TEST

class ModbusRegisterSensor {
 public:
  virtual void publish_state(uint16_t state) override;

 protected:
};

#endif // UNIT_TEST

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_REGISTER_SENSOR_H_