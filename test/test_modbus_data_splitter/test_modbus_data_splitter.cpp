#include <vector>

#include <Arduino.h>
#include <unity.h>

#include "modbus_data.h"
#include "modbus_data_splitter.h"
#include "modbus_frame.h"
#include <test_includes.h>

using std::vector;
using namespace esphome::modbus_spy;

void test_matching_pair_with_one_holding_register() {
  // Arrange
  ModbusDataSplitter data_splitter;
  uint8_t *request_data = new uint8_t[4] { 0x04, 0xAF, 0x00, 0x01 };
  ModbusFrame request(0x0B, 3, request_data, 4);
  uint8_t *response_data = new uint8_t[3] { 0x02, 0x34, 0x56 };
  ModbusFrame response(0x0B, 3, response_data, 3);

  // Act
  vector<ModbusData*>* split_data = data_splitter.split_request_and_response_data(&request, &response);

  // Assert
  TEST_ASSERT_TRUE(split_data != nullptr);
  TEST_ASSERT_EQUAL_UINT8(1, split_data->size());
  ModbusData* data1 = split_data->at(0);
  TEST_ASSERT_EQUAL_UINT8(0x0B, data1->address);
  TEST_ASSERT_EQUAL_UINT16(0x3456, data1->value);
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // ModbusDataSplitter tests
  RUN_TEST(test_matching_pair_with_one_holding_register);

  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}