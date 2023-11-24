#ifndef MODBUS_RESPONSE_DETECTOR_H_
#define MODBUS_RESPONSE_DETECTOR_H_

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#endif // UNIT_TEST

#include "modbus_frame.h"
#include "uart_interface.h"

namespace esphome {
namespace modbus_spy {

class IModbusResponseDetector {
 public:
  virtual ModbusFrame* detect_response() = 0;
};

class ModbusResponseDetector : public IModbusResponseDetector {
 private:
  static const uint16_t MAX_TIME_BETWEEN_REQUEST_AND_RESPONSE_IN_MS = 500;
  static const uint8_t MAX_TIME_BETWEEN_BYTES_IN_MS = 3;

 public:
  ModbusResponseDetector(IUartInterface* uart_interface);
  
 private:
  ModbusResponseDetector(ModbusResponseDetector&);

 public:
  ModbusFrame* detect_response();

 protected:
  IUartInterface* uart_interface_ { nullptr };
  uint32_t time_last_byte_received_ { 0 };

 private:
  bool read_next_byte(uint8_t* byte);
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_RESPONSE_DETECTOR_H_