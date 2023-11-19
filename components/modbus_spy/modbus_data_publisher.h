#ifndef MODBUS_DATA_PUBLISHER_H_
#define MODBUS_DATA_PUBLISHER_H_

#include <vector>

#include "modbus_data.h"
#include "modbus_frame_detector_factory.h"
#include "modbus_request_detector.h"
#include "modbus_response_detector.h"
#include "uart_interface.h"

namespace esphome {
namespace modbus_spy {

class IModbusDataPublisher {
 public:
  virtual void publish_data(std::vector<ModbusData*> data) = 0;
};

class ModbusDataPublisher : public IModbusDataPublisher {
 public:
  virtual void publish_data(std::vector<ModbusData*> data);
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_DATA_PUBLISHER_H_