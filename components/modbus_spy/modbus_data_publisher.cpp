#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST

#include "modbus_data_publisher.h"
#include "modbus_register_sensor.h"

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusDataPublisher";

void ModbusDataPublisher::add_register_sensor(
  uint8_t device_address, 
  uint16_t register_address,
  IModbusRegisterSensor* register_sensor
) {
  this->register_sensors_.insert({ register_address, register_sensor });
}

void ModbusDataPublisher::add_binary_sensor(
  uint8_t device_address, 
  uint16_t register_address, 
  IModbusBinarySensor* binary_sensor
) {
  this->binary_sensors_.insert({ register_address, binary_sensor });
}

void ModbusDataPublisher::publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data) {
  ESP_LOGD(TAG, "ModbusDataPublisher::publish_data");
  for (ModbusData* modbus_data : *data) {
    uint16_t data_model_register_address = convert_pdu_address_to_data_model_address(function, modbus_data->address);
    find_sensor_and_publish_data(device_address, data_model_register_address, modbus_data->value);
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

void ModbusDataPublisher::find_sensor_and_publish_data(uint8_t device_address, uint16_t data_model_register_address, uint16_t value) {
  ESP_LOGD(TAG, "Finding sensor for register address %d, to publish value %d", data_model_register_address, value);
  IModbusRegisterSensor *register_sensor = find_register_sensor(device_address, data_model_register_address);
  if (register_sensor != nullptr) {
    ESP_LOGD(TAG, "Found sensor!");
    register_sensor->publish_state(value);
  } else {
    IModbusBinarySensor *binary_sensor = this->binary_sensors_[data_model_register_address];
    if (binary_sensor != nullptr) {
      ESP_LOGD(TAG, "Found binary sensor! For register %d", data_model_register_address);
      binary_sensor->publish_state(static_cast<bool>(value));
    }
  }
}

IModbusRegisterSensor* ModbusDataPublisher::find_register_sensor(uint8_t device_address, uint16_t data_model_register_address) {
  return this->register_sensors_[data_model_register_address];
}

} //namespace modbus_spy
} //namespace esphome
