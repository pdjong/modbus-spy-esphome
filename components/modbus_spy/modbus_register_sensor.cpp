#ifndef UNIT_TEST

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST

#include "modbus_register_sensor.h"

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusRegisterSensor";

void ModbusRegisterSensor::publish_state(uint16_t state) {
  ESP_LOGD(TAG, "About to publish state: %d", state);
  this->sensor_->publish_state(static_cast<float>(state));
}

sensor::Sensor* ModbusRegisterSensor::get_sensor() const {
  return this->sensor_;
}

} //namespace modbus_spy
} //namespace esphome

#endif // UNIT_TEST