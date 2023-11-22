#ifndef UNIT_TEST

#include <iostream>

#include "esphome/core/log.h"

#include "modbus_spy.h"

using namespace std; 

namespace esphome {
namespace modbus_spy {

static const char *TAG = "modbus_spy";

void ModbusSpy::setup() {
  ESP_LOGI(TAG, "ModbusSpy::setup");
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