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

#include "modbus_sniffer.h"
// #include "modbus_frame.h"

using namespace std; 

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusSniffer";

void ModbusSniffer::start_sniffing()
{
  xTaskCreatePinnedToCore(ModbusSniffer::sniff_loop_task,
                              "sniff_task", // name
                              50000,        // stack size (in words)
                              this,         // input params
                              1,            // priority
                              nullptr,      // Handle, not needed
                              0             // core
  );
}

void ModbusSniffer::sniff_loop_task(void* params) {
  ModbusSniffer *modbus_sniffer = reinterpret_cast<ModbusSniffer*>(params);
  while (true) {
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



    // // 7. It is a response! Check if it matches the request
    // const bool response_matches_request = modbus_sniffer->does_response_match_request(response, request);

    // // 8. If the response does not match the request, start over
    // if (!response_matches_request) {
    //   // TODO
    //   continue;
    // }

    // // The response matches the request! Check if we're interested in the data:
    // // 9. Handle the data
    // modbus_sniffer->handle_data_in_request_response(request, response);
    
    delay(1);
  }
}

} // namespace modbus_spy
} // namespace esphome