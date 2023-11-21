#ifndef FAKE_MODBUS_DATA_PUBLISHER_
#define FAKE_MODBUS_DATA_PUBLISHER_

#include <vector>

#include "modbus_data.h"
#include "modbus_data_publisher.h"
#include "modbus_register_sensor.h"

using std::vector;
using esphome::modbus_spy::IModbusDataPublisher;
using esphome::modbus_spy::IModbusRegisterSensor;
using esphome::modbus_spy::ModbusData;

typedef struct PublishedData {
  uint8_t device_address;
  uint8_t function;
  ModbusData* modbus_data;
} PublishedData;

class FakeModbusDataPublisher : public IModbusDataPublisher {
 public:
  virtual void publish_data(uint8_t device_address, uint8_t function, std::vector<ModbusData*>* data);
  virtual void add_register_sensor(uint8_t device_address, uint16_t register_address, IModbusRegisterSensor* register_sensor) override;
  const vector<PublishedData*> get_published_data() const { return this->published_data_; }
  
 protected:
  vector<PublishedData*> published_data_;
};


#endif // FAKE_MODBUS_DATA_PUBLISHER_