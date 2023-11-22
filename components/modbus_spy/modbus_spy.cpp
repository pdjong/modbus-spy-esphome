#ifndef UNIT_TEST

#include <iostream>

#include "esphome/core/log.h"

#include "modbus_spy.h"

using namespace std; 

namespace esphome {
namespace modbus_spy {

static const char *TAG = "modbus_spy";

ModbusSpy::ModbusSpy() {
  Esp32ArduinoUartInterface *uart_interface = new Esp32ArduinoUartInterface(this);
  this->sniffer_ = new ModbusSniffer(uart_interface, &this->data_publisher_);
}

sensor::Sensor* ModbusSpy::create_sensor(uint8_t device_address, uint16_t register_address) {
  ModbusRegisterSensor *register_sensor = new ModbusRegisterSensor();
  this->data_publisher_.add_register_sensor(device_address, register_address, register_sensor);
  return register_sensor->get_sensor();
}

void ModbusSpy::setup() {
  ESP_LOGD(TAG, "ModbusSpy::setup");
  this->sniffer_->start_sniffing();
}

void ModbusSpy::loop() {
  delay(5);
}

float ModbusSpy::get_setup_priority() const {
  // After UART bus
  return setup_priority::BUS - 1.0f;
}

void ModbusSpy::dump_config() {
  ESP_LOGCONFIG(TAG, "ModbusSpy");
}

} // namespace modbus_spy
} // namespace esphome

#endif // UNIT_TEST