// #include <iostream>
// #include <sstream>
#include <vector>

#include <Arduino.h>
#ifdef UNIT_TEST
#include <test_includes.h>
#else
#include "esphome/core/datatypes.h"
#include "esphome/core/log.h"
#endif // UNIT_TEST
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "modbus_data.h"
#include "modbus_data_splitter.h"
#include "modbus_frame.h"
#include "modbus_frame_detector_factory.h"
#include "modbus_sniffer.h"

using std::vector;

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusSniffer";

void ModbusSniffer::start_sniffing() {
  xTaskCreatePinnedToCore(ModbusSniffer::sniff_loop_task,
                              "sniff_task", // name
                              50000,        // stack size (in words)
                              this,         // input params
                              1,            // priority
                              nullptr,      // Handle, not needed
                              0             // core
  );
}

void ModbusSniffer::stop_sniffing() {
  this->should_stop_sniffing_ = true;
  while (this->is_sniffing_) {
    delay(1);
  }
}

void ModbusSniffer::sniff_loop_task(void* params) {
  ModbusSniffer *modbus_sniffer = reinterpret_cast<ModbusSniffer*>(params);
  IModbusRequestDetector *request_detector = 
    ModbusFrameDetectorFactory::create_request_detector(modbus_sniffer->uart_interface_);
  IModbusResponseDetector *response_detector =
    ModbusFrameDetectorFactory::create_response_detector(modbus_sniffer->uart_interface_);
  ModbusDataSplitter data_splitter;

  while (true) {
    if (modbus_sniffer->should_stop_sniffing_) {
      vTaskDelete(NULL);
      break;
    }

    //  1. Wait for incoming data
    //  2. Receive entire request
    //  3. If not a request, discard the data, empty the entire receive buffer and start over
    //  4. It is a request, so wait for incoming data
    //  5. Receive entire response
    //  6. If not a response, discard the data, empty the entire receive buffer and start over
    //  7. It is a response! Check if it matches the request
    //  8. If the response does not match the request, start over
    //     The response matches the request!
    //  9. Handle the data

    ModbusFrame *request_frame = request_detector->detect_request();
    if (nullptr == request_frame) {
      // TODO: Empty UART RX buffer
      continue;
    }
    ModbusFrame *response_frame = response_detector->detect_response();
    if (nullptr == response_frame) {
      // TODO: Empty UART RX buffer
      continue;
    }
    vector<ModbusData*> *split_data = data_splitter.split_request_and_response_data(request_frame, response_frame);
    if (nullptr == split_data) {
      // TODO: Empty UART RX buffer
      continue;
    }
    uint8_t device_address = request_frame->get_address();
    uint8_t function = request_frame->get_function();
    modbus_sniffer->data_publisher_->publish_data(device_address, function, split_data);

    delay(1);
  }
}

} // namespace modbus_spy
} // namespace esphome