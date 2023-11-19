#include <vector>

#include "fake_modbus_data_publisher.h"
#include "modbus_data.h"
#include "modbus_data_publisher.h"

using std::vector;

void FakeModbusDataPublisher::publish_data(vector<ModbusData*> data) {
  for (ModbusData* data_item : data) {
    this->published_data_.push_back(data_item);
  }
}