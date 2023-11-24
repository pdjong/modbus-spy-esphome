#ifndef MODBUS_DATA_PUBLISHER_H_
#define MODBUS_DATA_PUBLISHER_H_

#include <map>
#include <vector>

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#endif // UNIT_TEST

#include "modbus_binary_sensor.h"
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
  virtual void add_register_sensor(uint8_t device_address, uint16_t register_address, IModbusRegisterSensor* register_sensor) = 0;
  virtual void add_binary_sensor(uint8_t device_address, uint16_t register_address, IModbusBinarySensor* binary_sensor) = 0;
  virtual void publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) = 0;
};

class ModbusDataPublisher : public IModbusDataPublisher {
 public:
  virtual void add_register_sensor(uint8_t device_address, uint16_t register_address, IModbusRegisterSensor* register_sensor) override;
  virtual void add_binary_sensor(uint8_t device_address, uint16_t register_address, IModbusBinarySensor* binary_sensor) override;
  virtual void publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) override;

 protected:
  std::map<uint16_t, IModbusRegisterSensor*> register_sensors_;
  std::map<uint16_t, IModbusBinarySensor*> binary_sensors_;
  IModbusRegisterSensor* find_register_sensor(uint8_t device_address, uint16_t data_model_register_address);

 private:
  uint16_t convert_pdu_address_to_data_model_address(uint8_t function, uint16_t pdu_address);
  void find_sensor_and_publish_data(uint8_t device_address, uint16_t data_model_register_address, uint16_t value);
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_DATA_PUBLISHER_H_