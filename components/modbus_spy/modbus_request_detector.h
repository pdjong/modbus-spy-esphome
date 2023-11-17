#ifndef MODBUS_REQUEST_DETECTOR_H_
#define MODBUS_REQUEST_DETECTOR_H_

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
// #include "esphome/core/log.h"
#endif // UNIT_TEST

#include "modbus_frame.h"
#include "uart_interface.h"

namespace esphome {
namespace modbus_spy {

class ModbusRequestDetector {
 private:
  static const uint8_t MAX_TIME_BETWEEN_BYTES_IN_MS = 3;

 public:
  ModbusRequestDetector(IUartInterface* uart_interface) : uart_interface_(uart_interface) {}
  
 private:
  ModbusRequestDetector(ModbusRequestDetector&);

 public:
  ModbusFrame* detect_request();

 protected:
  IUartInterface* uart_interface_ { nullptr };
  uint32_t time_last_byte_received_ { 0 };

 private:
  bool read_next_byte(uint8_t* byte);
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_REQUEST_DETECTOR_H_