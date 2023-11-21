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
  //this->register_sensors_.insert(std::pair<uint16_t, IModbusRegisterSensor*>(register_address, register_sensor));
  this->register_sensors_.insert({ register_address, register_sensor });
}

void ModbusDataPublisher::publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) {
  for (ModbusData* modbus_data : *data) {
    uint16_t data_model_register_address = convert_pdu_address_to_data_model_address(function, modbus_data->address);
    find_sensor_and_publish_data(data_model_register_address, modbus_data->value);
  }
}

uint16_t ModbusDataPublisher::convert_pdu_address_to_data_model_address(uint8_t function, uint16_t pdu_address) {
  // Convert the register address in ModbusData to an actual register address, based on the function.
  // Function 3: add 40001
  uint16_t modbus_data_model_address { 0 };
  switch (function) {
    case 3: {
      modbus_data_model_address = pdu_address + 40001;
      break;
    }
    default:
      break;
  }

  return modbus_data_model_address;
}

void ModbusDataPublisher::find_sensor_and_publish_data(uint16_t data_model_register_address, uint16_t value) {
  IModbusRegisterSensor *register_sensor = this->register_sensors_[data_model_register_address];
  if (register_sensor != nullptr) {
    register_sensor->publish_state(value);
  }
}

} //namespace modbus_spy
} //namespace esphome
