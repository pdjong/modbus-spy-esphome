#include <map>
#include <vector>

#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST

#include "modbus_binary_sensor.h"
#include "modbus_data_publisher.h"
#include "modbus_register_sensor.h"

using std::vector;

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusDataPublisher";

void ModbusDataPublisher::add_register_sensor(
  uint8_t device_address, 
  uint16_t register_address,
  IModbusRegisterSensor* register_sensor
) {
  std::map<uint16_t, IModbusRegisterSensor*> *register_sensors_for_device = get_register_sensors_for_device(device_address);
  register_sensors_for_device->insert({ register_address, register_sensor });
}

void ModbusDataPublisher::add_binary_sensor(
  uint8_t device_address, 
  uint16_t register_address, 
  IModbusBinarySensor* binary_sensor
) {
  std::map<uint16_t, IModbusBinarySensor*> *binary_sensors_for_device = get_binary_sensors_for_device(device_address);
  binary_sensors_for_device->insert({ register_address, binary_sensor });
}

std::map<uint16_t, IModbusRegisterSensor*>* ModbusDataPublisher::get_register_sensors_for_device(uint8_t device_address) {
  DeviceSensors *sensors_for_device = get_sensors_for_device(device_address);
std::map<uint16_t, IModbusRegisterSensor*>* register_sensors_for_device = sensors_for_device->register_sensors_;
  if (nullptr == register_sensors_for_device) {
    register_sensors_for_device = new std::map<uint16_t, IModbusRegisterSensor*>;
    sensors_for_device->register_sensors_ = register_sensors_for_device;
  }
  return register_sensors_for_device;
}

std::map<uint16_t, IModbusBinarySensor*>* ModbusDataPublisher::get_binary_sensors_for_device(uint8_t device_address) {
  DeviceSensors *sensors_for_device = get_sensors_for_device(device_address);
  std::map<uint16_t, IModbusBinarySensor*>* binary_sensors_for_device = sensors_for_device->binary_sensors_;
  if (nullptr == binary_sensors_for_device) {
    binary_sensors_for_device = new std::map<uint16_t, IModbusBinarySensor*>;
    sensors_for_device->binary_sensors_ = binary_sensors_for_device;
  }
  return binary_sensors_for_device;
}

ModbusDataPublisher::DeviceSensors* ModbusDataPublisher::get_sensors_for_device(uint8_t device_address) {
  DeviceSensors *sensors_for_device = this->device_sensors_[device_address];
  if (nullptr == sensors_for_device) {
    sensors_for_device = new DeviceSensors;
    this->device_sensors_[device_address] = sensors_for_device;
  }
  return sensors_for_device;
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
    IModbusBinarySensor *binary_sensor = find_binary_sensor(device_address, data_model_register_address);
    if (binary_sensor != nullptr) {
      ESP_LOGD(TAG, "Found binary sensor! For register %d", data_model_register_address);
      binary_sensor->publish_state(static_cast<bool>(value));
    }
  }
}

IModbusRegisterSensor* ModbusDataPublisher::find_register_sensor(uint8_t device_address, uint16_t data_model_register_address) {
  DeviceSensors *device_sensors = this->device_sensors_[device_address];
  if (nullptr == device_sensors) {
    return nullptr;
  }
  if (nullptr == device_sensors->register_sensors_) {
    return nullptr;
  }
  std::map<uint16_t, IModbusRegisterSensor*>& register_sensors_for_device = *device_sensors->register_sensors_;
  return register_sensors_for_device[data_model_register_address];
}

IModbusBinarySensor* ModbusDataPublisher::find_binary_sensor(uint8_t device_address, uint16_t data_model_register_address) {
  DeviceSensors *device_sensors = this->device_sensors_[device_address];
  if (nullptr == device_sensors) {
    return nullptr;
  }
  if (nullptr == device_sensors->binary_sensors_) {
    return nullptr;
  }
  std::map<uint16_t, IModbusBinarySensor*>& binary_sensors_for_device = *device_sensors->binary_sensors_;
  return binary_sensors_for_device[data_model_register_address];
}


} //namespace modbus_spy
} //namespace esphome
