#include <vector>

#include "modbus_data.h"
#include "modbus_data_splitter.h"
#include "modbus_frame.h"

using std::vector;

namespace esphome {
namespace modbus_spy {

vector<ModbusData*>* ModbusDataSplitter::split_data(ModbusFrame* request, ModbusFrame* response) {
  return nullptr;
}

} //namespace modbus_spy
} //namespace esphome
