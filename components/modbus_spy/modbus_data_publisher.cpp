#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#endif // UNIT_TEST

#include "modbus_data_publisher.h"
#include "modbus_register_sensor.h"

namespace esphome {
namespace modbus_spy {

void ModbusDataPublisher::add_register_sensor(
  uint8_t device_address, 
  uint16_t register_address,
  IModbusRegisterSensor* register_sensor
) {
  
}

void ModbusDataPublisher::publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) {

}

} //namespace modbus_spy
} //namespace esphome
