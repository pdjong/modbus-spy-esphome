#ifndef MODBUS_SPY_H_
#define MODBUS_SPY_H_

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
// #include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <map>

#include "esp32_arduino_uart_interface.h"
#include "modbus_data_publisher.h"
#include "modbus_register_sensor.h"
#include "modbus_sniffer.h"

namespace esphome {
namespace modbus_spy {

class ModbusSpy : public Component, public uart::UARTDevice {
 public:
  ModbusSpy() {
    Esp32ArduinoUartInterface *uart_interface = new Esp32ArduinoUartInterface(this);
    this->sniffer_ = new ModbusSniffer(uart_interface, &this->data_publisher_);
  }

  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override;
  sensor::Sensor* create_sensor(uint8_t device_address, uint16_t register_address) {
    ModbusRegisterSensor *register_sensor = new ModbusRegisterSensor();
    this->data_publisher_.add_register_sensor(device_address, register_address, register_sensor);
    return register_sensor->get_sensor();
  }

 protected:
  ModbusSniffer* sniffer_;
  ModbusDataPublisher data_publisher_;
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_SPY_H_