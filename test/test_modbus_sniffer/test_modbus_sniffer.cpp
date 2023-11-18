#include <Arduino.h>
#include <unity.h>

#include "fake_uart_interface.h"
#include "modbus_frame.h"
#include "modbus_request_detector.h"
#include <test_includes.h>

using namespace esphome::modbus_spy;

void setUp(void) {}
void tearDown(void) {}

void test_modbus_request_detector_request_function_3_bytes_coming_in_live() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xF4, 0x79 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_FALSE(nullptr == request_frame);
  TEST_ASSERT_EQUAL_UINT8(0x0B, request_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x03, request_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(4, request_frame->get_data_length());
  
  const uint8_t *actual_data = request_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x04, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0xAF, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x00, actual_data[2]);
  TEST_ASSERT_EQUAL_UINT8(0x1E, actual_data[3]);
}

void test_modbus_request_detector_request_function_3_bytes_already_received() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xF4, 0x79 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 1,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );
  delayMicroseconds(100);

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_FALSE(nullptr == request_frame);
  TEST_ASSERT_EQUAL_UINT8(0x0B, request_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x03, request_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(4, request_frame->get_data_length());
  
  const uint8_t *actual_data = request_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x04, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0xAF, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x00, actual_data[2]);
  TEST_ASSERT_EQUAL_UINT8(0x1E, actual_data[3]);
}

void test_modbus_request_detector_wrong_crc_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xFF, 0xFF };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_receive_timeout_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xFF, 0xFF };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 6 * 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_response_function_3_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x3C, 0x13, 0x9B, 0x11, 0x10, 0x17 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_request_function_15() {}

void test_modbus_request_detector_unsupported_function_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x08, 0x00, 0x01, 0x00, 0x00, 0x61, 0xB1 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8
  };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    nullptr,                    // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  // Delay 4 ms to make sure that the fake uart task is done
  delay(4);

  // Assert
  uint8_t *raw_data = new uint8_t[6] { 0x0B, 0x08, 0x00, 0x01, 0x00, 0x00 };
  uint16_t correct_crc = esphome::crc16(raw_data, 6);
  TEST_ASSERT_EQUAL_UINT16(correct_crc, 0x61B1);
  TEST_ASSERT_TRUE(nullptr == request_frame);
}


int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_modbus_request_detector_request_function_3_bytes_coming_in_live);
  RUN_TEST(test_modbus_request_detector_request_function_3_bytes_already_received);
  RUN_TEST(test_modbus_request_detector_wrong_crc_results_in_nullptr);
  RUN_TEST(test_modbus_request_detector_response_function_3_results_in_nullptr);
  // RUN_TEST(test_modbus_request_detector_request_function_15);
  RUN_TEST(test_modbus_request_detector_unsupported_function_results_in_nullptr);
  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}
