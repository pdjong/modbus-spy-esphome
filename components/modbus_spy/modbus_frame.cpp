#include "modbus_frame.h"

namespace esphome {
namespace modbus_spy {

ModbusFrame::~ModbusFrame() {
  if (this->data_ != nullptr) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
}

} //namespace modbus_spy
} //namespace esphome
