#include <Arduino.h>
#include <unity.h>

#include "fake_uart_interface.h"
#include "modbus_frame.h"
#include "modbus_request_detector.h"
#include <test_includes.h>

using namespace esphome::modbus_spy;

void setUp(void) {}
void tearDown(void) {}

void test_modbus_request_detector_request_function_1() {
  // Arrange
  FakeUartInterface uart_interface;
  ModbusRequestDetector modbus_request_detector(&uart_interface);

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_FALSE(nullptr == request_frame);
}

// void test_data_link_layer_req_ud2_different_l_fields(void) {
//   // Arrange
//   FakeUartInterface uart_interface;
//   const uint8_t fake_data[] = { 0x68, 0x06, 0x05, 0x68, 0x08, 0xB2, 0x72, 0x03, 0x02, 0x01, 0x32, 0x16 };
//   FakeUartInterfaceTaskArgs args = { 
//     .uart_interface = &uart_interface,
//     .respond_to_nth_write = 1,
//     .delay_in_ms  = 5,
//     .data_to_return = fake_data,
//     .len_of_data_to_return = 12
//   };
//   xTaskCreatePinnedToCore(fake_uart_interface_task,
//                     "fake_uart_interface_task", // name
//                     30000,                      // stack size (in words)
//                     &args,                      // input params
//                     1,                          // priority
//                     nullptr,                    // Handle, not needed
//                     0                           // core
//   );

//   TestableDataLinkLayer data_link_layer(&uart_interface);
//   data_link_layer.set_meter_is_initialized(true);

//   // Act
//   const uint8_t a = 0xB2;
//   MbusReader::DataLinkLayer::LongFrame response_frame;
//   const bool actual_return_value = data_link_layer.req_ud2(a, &response_frame);

//   // Assert
//   TEST_ASSERT_FALSE(actual_return_value);
// }

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_modbus_request_detector_request_function_1);
  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}
