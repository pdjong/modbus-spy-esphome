#ifndef MODBUS_SPY_H_
#define MODBUS_SPY_H_

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

#include "esp32_arduino_uart_interface.h"
#include "modbus_data_publisher.h"
#include "modbus_sniffer.h"

namespace esphome {
namespace modbus_spy {

class ModbusSpy : public Component, public uart::UARTDevice {
 public:
  ModbusSpy();

  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override;
  sensor::Sensor* create_sensor(uint8_t device_address, uint16_t register_address);
  binary_sensor::BinarySensor* create_binary_sensor(uint8_t device_address, uint16_t register_address);

 protected:
  ModbusSniffer* sniffer_;
  ModbusDataPublisher data_publisher_;
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_SPY_H_