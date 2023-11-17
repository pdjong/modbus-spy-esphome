#ifndef MODBUS_REQUEST_H_
#define MODBUS_REQUEST_H_

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST

namespace esphome {
namespace modbus_spy {

class ModbusFrame {
 public:
  void set_address(uint8_t address) { this->address_ = address; }
  void set_function(uint8_t function) { this->function_ = function; }
  void set_data(uint8_t* data) { this->data_ = data; }
  void set_received_crc(uint16_t received_crc) { this->received_crc_ = received_crc; }

 protected:
  uint8_t address_;
  uint8_t function_;
  uint8_t* data_;
  uint16_t received_crc_;
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_REQUEST_H_