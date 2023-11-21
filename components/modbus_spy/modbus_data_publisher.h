#ifndef MODBUS_DATA_PUBLISHER_H_
#define MODBUS_DATA_PUBLISHER_H_

#include <vector>

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#endif // UNIT_TEST

#include "modbus_data.h"
#include "modbus_frame_detector_factory.h"
#include "modbus_register_sensor.h"
#include "modbus_request_detector.h"
#include "modbus_response_detector.h"
#include "uart_interface.h"

namespace esphome {
namespace modbus_spy {

class IModbusDataPublisher {
 public:
  virtual void publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) = 0;
  virtual void add_register_sensor(uint8_t device_address, uint16_t register_address, IModbusRegisterSensor* register_sensor) = 0;
};

class ModbusDataPublisher : public IModbusDataPublisher {
 public:
  virtual void publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) override;
  virtual void add_register_sensor(uint8_t device_address, uint16_t register_address, IModbusRegisterSensor* register_sensor) override;
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_DATA_PUBLISHER_H_