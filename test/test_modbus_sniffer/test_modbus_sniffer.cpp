#include <vector>

#include <Arduino.h>
#include <unity.h>

#include "fake_modbus_data_publisher.h"
#include "fake_uart_interface.h"
#include "modbus_data.h"
#include "modbus_frame.h"
#include "modbus_frame_detector_factory.h"
#include "modbus_response_detector.h"
#include "modbus_request_detector.h"
#include "modbus_sniffer.h"
#include <test_includes.h>

using std::vector;
using namespace esphome::modbus_spy;

// What to test?
// - combination of actual request- and response detector, using fake uart interface
// - combination of matching and non-matching results of detectors, using fake detectors

void test_modbus_sniffer_with_actual_detectors_good() {
  // Arrange
  FakeUartInterface fake_uart_interface;
  uint8_t fake_data[] = { 0x02, 0x03, 0x04, 0xAF, 0x00, 0x01, 0xB5, 0x28, 0x02, 0x03, 0x02, 0x34, 0x56, 0x6A, 0xBA };
  FakeModbusDataPublisher fake_data_publisher;
  ModbusSniffer modbus_sniffer(&fake_uart_interface, &fake_data_publisher);
  bool uart_task_should_stop = false;
  FakeUartInterfaceTaskArgs args = { 
    .uart_interface = &fake_uart_interface,
    .initial_delay_in_ms = 0,
    .delay_between_bytes_in_us = 573,
    .data_to_return = fake_data,
    .len_of_data_to_return = 15,
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
  modbus_sniffer.start_sniffing();
  delay(10);
  uart_task_should_stop = true;
  // Delay 5 ms to make sure that the fake uart task is done
  delay(5);

  // Assert
  vector<ModbusData*> published_data = fake_data_publisher.get_published_data();
  TEST_ASSERT_EQUAL_UINT8(1, published_data.size());
  ModbusData* data = published_data.at(1);
  TEST_ASSERT_EQUAL_UINT16(0x04AF, data->address);
  TEST_ASSERT_EQUAL_UINT16(0x3456, data->value);
}

void generate_crc() {
  uint8_t crc_data[] = { 0x02, 0x03, 0x04, 0xAF, 0x00, 0x01 };
  uint16_t expected_crc = esphome::crc16(crc_data, 6);
  TEST_ASSERT_EQUAL_UINT16(expected_crc, 0);
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // ModbusSniffer tests
  RUN_TEST(test_modbus_sniffer_with_actual_detectors_good);

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