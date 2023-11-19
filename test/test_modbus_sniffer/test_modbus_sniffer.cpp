#include <Arduino.h>
#include <unity.h>

#include "fake_uart_interface.h"
#include "modbus_frame.h"
#include "modbus_response_detector.h"
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
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

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
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 1,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );
  delayMicroseconds(100);

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

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
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_receive_timeout_in_between_characters_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xFF, 0xFF };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 6 * 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_response_function_3_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x3C, 0x13, 0x9B, 0x11, 0x10, 0x17 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

void test_modbus_request_detector_request_function_15() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x0F, 0x00, 0x10, 0x00, 0x09, 0x02, 0x55, 0x01, 0x67, 0xDC };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 11,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_FALSE(nullptr == request_frame);
  TEST_ASSERT_EQUAL_UINT8(0x0B, request_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x0F, request_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(7, request_frame->get_data_length());
  
  const uint8_t *actual_data = request_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x00, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0x10, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x00, actual_data[2]);
  TEST_ASSERT_EQUAL_UINT8(0x09, actual_data[3]);
  TEST_ASSERT_EQUAL_UINT8(0x02, actual_data[4]);
  TEST_ASSERT_EQUAL_UINT8(0x55, actual_data[5]);
  TEST_ASSERT_EQUAL_UINT8(0x01, actual_data[6]);
}

void test_modbus_request_detector_unsupported_function_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x08, 0x00, 0x01, 0x00, 0x00, 0x61, 0xB1 };
  ModbusRequestDetector modbus_request_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *request_frame = modbus_request_detector.detect_request();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  uint8_t *raw_data = new uint8_t[6] { 0x0B, 0x08, 0x00, 0x01, 0x00, 0x00 };
  TEST_ASSERT_TRUE(nullptr == request_frame);
}

/// -- ModbusResponseDetector --
void test_modbus_response_detector_response_function_3_directly_available() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x03, 0x02, 0x34, 0x56, 0x6A, 0xBA };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 7,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_FALSE(nullptr == response_frame);
  TEST_ASSERT_EQUAL_UINT8(0x02, response_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x03, response_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(3, response_frame->get_data_length());
  
  const uint8_t *actual_data = response_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x02, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0x34, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x56, actual_data[2]);
}

void test_modbus_response_detector_response_function_3_available_after_50ms() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x03, 0x02, 0x34, 0x56, 0x6A, 0xBA };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = {
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 50,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 7,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_FALSE(nullptr == response_frame);
  TEST_ASSERT_EQUAL_UINT8(0x02, response_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x03, response_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(3, response_frame->get_data_length());
  
  const uint8_t *actual_data = response_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x02, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0x34, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x56, actual_data[2]);
}

void test_modbus_response_detector_wrong_crc_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x03, 0x02, 0x34, 0x56, 0x6A, 0x00 };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 2,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 7,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == response_frame);
}

void test_modbus_response_detector_request_function_3_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x03, 0x04, 0xAF, 0x00, 0x1E, 0xF4, 0x79 };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 2,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == response_frame);
}

void test_modbus_response_detector_unsupported_function_results_in_nullptr() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x0B, 0x07, 0x04, 0x03, 0xF1 };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 2,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 5,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_TRUE(nullptr == response_frame);
}

void test_modbus_response_detector_response_function_1() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x01, 0x01, 0x5A, 0xD1, 0xF7 };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 2,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 6,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_FALSE(nullptr == response_frame);
  TEST_ASSERT_EQUAL_UINT8(0x02, response_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x01, response_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(2, response_frame->get_data_length());
  
  const uint8_t *actual_data = response_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x01, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0x5A, actual_data[1]);
}

void test_modbus_response_detector_response_function_6() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x06, 0x01, 0x23, 0x98, 0x76, 0x93, 0xE9 };
  ModbusResponseDetector modbus_response_detector(&fake_uart_interface);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 2,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 8,
    .should_stop = &uart_task_should_stop
  };
  TaskHandle_t uart_task_handle { nullptr };
  xTaskCreatePinnedToCore(fake_uart_interface_task,
                    "fake_uart_interface_task", // name
                    30000,                      // stack size (in words)
                    &args,                      // input params
                    1,                          // priority
                    &uart_task_handle,          // Handle, not needed
                    0                           // core
  );

  // Act
  ModbusFrame *response_frame = modbus_response_detector.detect_response();
  uart_task_should_stop = true;
  // Delay 1 ms to make sure that the fake uart task is done
  delay(1);

  // Assert
  TEST_ASSERT_FALSE(nullptr == response_frame);
  TEST_ASSERT_EQUAL_UINT8(0x02, response_frame->get_address());
  TEST_ASSERT_EQUAL_UINT8(0x06, response_frame->get_function());
  TEST_ASSERT_EQUAL_UINT8(4, response_frame->get_data_length());
  
  const uint8_t *actual_data = response_frame->get_data();
  TEST_ASSERT_EQUAL_UINT8(0x01, actual_data[0]);
  TEST_ASSERT_EQUAL_UINT8(0x23, actual_data[1]);
  TEST_ASSERT_EQUAL_UINT8(0x98, actual_data[2]);
  TEST_ASSERT_EQUAL_UINT8(0x76, actual_data[3]);
}

void generate_crc() {
  uint8_t crc_data[] = { 0x0B, 0x0F, 0x00, 0x10, 0x00, 0x09, 0x02, 0x55, 0x01 };
  uint16_t expected_crc = esphome::crc16(crc_data, 9);
  TEST_ASSERT_EQUAL_UINT16(expected_crc, 0);
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // ModbusRequestDetector tests
  RUN_TEST(test_modbus_request_detector_request_function_3_bytes_coming_in_live);
  RUN_TEST(test_modbus_request_detector_request_function_3_bytes_already_received);
  RUN_TEST(test_modbus_request_detector_wrong_crc_results_in_nullptr);
  RUN_TEST(test_modbus_request_detector_receive_timeout_in_between_characters_results_in_nullptr);
  RUN_TEST(test_modbus_request_detector_response_function_3_results_in_nullptr);
  RUN_TEST(test_modbus_request_detector_request_function_15);
  RUN_TEST(test_modbus_request_detector_unsupported_function_results_in_nullptr);

  // ModbusResponseDetector tests
  RUN_TEST(test_modbus_response_detector_response_function_3_directly_available);
  RUN_TEST(test_modbus_response_detector_response_function_3_available_after_50ms);
  RUN_TEST(test_modbus_response_detector_wrong_crc_results_in_nullptr);
  RUN_TEST(test_modbus_response_detector_request_function_3_results_in_nullptr);
  RUN_TEST(test_modbus_response_detector_unsupported_function_results_in_nullptr);
  
  RUN_TEST(test_modbus_response_detector_response_function_1);
  RUN_TEST(test_modbus_response_detector_response_function_6);

  // CRC generation tool :P
  // RUN_TEST(generate_crc);

  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}
