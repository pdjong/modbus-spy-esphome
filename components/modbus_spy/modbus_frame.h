#ifndef MODBUS_FRAME_H_
#define MODBUS_FRAME_H_

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
  ModbusFrame() : address_(0), function_(0), data_(nullptr), received_crc_(0) {}
  ~ModbusFrame();

 private:
  ModbusFrame(const ModbusFrame&);

 public:
  void set_address(uint8_t address) { this->address_ = address; }
  void set_function(uint8_t function) { this->function_ = function; }
  void set_data(uint8_t* data, uint8_t length) { this->data_ = data; this->data_length_ = length; }
  void set_received_crc(uint16_t received_crc) { this->received_crc_ = received_crc; }

  uint8_t get_address() const { return this->address_; }
  uint8_t get_function() const { return this->function_; }
  uint8_t* get_data() const { return this->data_; }
  uint8_t get_data_length() const { return this->data_length_; }
  uint16_t get_received_crc() const { return this->received_crc_; }

 protected:
  uint8_t address_;
  uint8_t function_;
  uint8_t* data_;
  uint8_t data_length_;
  uint16_t received_crc_;
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_FRAME_H_