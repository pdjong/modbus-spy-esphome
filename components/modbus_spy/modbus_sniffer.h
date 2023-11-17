#pragma once

#include <vector>

// #include "modbus_frame.h"

namespace esphome {
namespace modbus_spy {

class ModbusSniffer {
  public:  

  protected:
    // std::vector<uint8_t> rx_buffer_;
    // void log_rx_buffer();
    
  public:
    void start_sniffing();
    static void sniff_loop_task(void* params);

  private:
    // ModbusRequest* receive_request();
};

} //namespace modbus_spy
} //namespace esphome