/* defrost: 20, 24, 25 */

#include <iostream>
#include <vector>
#include <sstream>

#include "esphome/core/log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "modbus_spy.h"
// #include "modbus_request.h"

using namespace std; 

namespace esphome {
namespace modbus_spy {

static const char *TAG = "modbus_spy";

void ModbusSpy::loop()
{
  delay(5);
}

float ModbusSpy::get_setup_priority() const
{
  // After UART bus
  return setup_priority::BUS - 1.0f;
}

void ModbusSpy::dump_config()
{
  ESP_LOGCONFIG(TAG, "ModbusSpy");
  //LOG_SENSOR("  ", "Heat Exchanger Water Outlet Temperature", this->heat_exchanger_water_outlet_temperature_sensor_);
  //LOG_SENSOR("  ", "Heat Exchanger Water Inlet Temperature", this->heat_exchanger_water_inlet_temperature_sensor_);
  //LOG_SENSOR("  ", "Compressor Working Speed", this->compressor_working_speed_sensor_);
}

} // namespace modbus_spy
} // namespace esphome