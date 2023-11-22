#ifndef MODBUS_SNIFFER_H_
#define MODBUS_SNIFFER_H_

#include "modbus_data_publisher.h"
#include "modbus_frame_detector_factory.h"
#include "modbus_request_detector.h"
#include "modbus_response_detector.h"
#include "uart_interface.h"

namespace esphome {
namespace modbus_spy {

class ModbusSniffer {
 public:
  ModbusSniffer(IUartInterface* uart_interface, IModbusDataPublisher* data_publisher) :
    uart_interface_(uart_interface), data_publisher_(data_publisher) {}
  void start_sniffing();
  void stop_sniffing();

 protected:
  IUartInterface* uart_interface_;
  IModbusDataPublisher* data_publisher_;
  bool should_stop_sniffing_ { false };
  bool is_sniffing_ { false };

 private:
  static void sniff_loop_task(void* params);
  void empty_rx_buffer();
};

} //namespace modbus_spy
} //namespace esphome

#endif // MODBUS_SNIFFER_H_