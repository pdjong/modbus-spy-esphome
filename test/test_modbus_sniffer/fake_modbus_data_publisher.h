#ifndef FAKE_MODBUS_DATA_PUBLISHER_
#define FAKE_MODBUS_DATA_PUBLISHER_

#include <vector>

#include "modbus_data.h"
#include "modbus_data_publisher.h"

using std::vector;
using esphome::modbus_spy::IModbusDataPublisher;
using esphome::modbus_spy::ModbusData;

class FakeModbusDataPublisher : public IModbusDataPublisher {
 public:
  virtual void publish_data(std::vector<ModbusData*> data);
  const vector<ModbusData*> get_published_data() const { return this->published_data_; }
  
 protected:
  vector<ModbusData*> published_data_;
};


#endif // FAKE_MODBUS_DATA_PUBLISHER_