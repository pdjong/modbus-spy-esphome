#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <map>

#include "modbus_frame.h"

namespace esphome {
namespace modbus_spy {

class ModbusSpy : public Component, public uart::UARTDevice {
  public:  
    void setup() override;
    void loop() override;
    void dump_config() override;
    float get_setup_priority() const override;

  protected:
    std::vector<uint8_t> rx_buffer_;
    void log_rx_buffer();
    
  public:
    static void read_loop_task(void* params);

  private:
    ModbusFrame* receive_request();
};

} //namespace modbus_spy
} //namespace esphome