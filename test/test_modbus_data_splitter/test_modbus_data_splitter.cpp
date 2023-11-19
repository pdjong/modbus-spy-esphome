#include <vector>

#include <Arduino.h>
#include <unity.h>

#include "modbus_data.h"
#include "modbus_frame.h"
#include <test_includes.h>

using std::vector;
using namespace esphome::modbus_spy;

void test_something() {
  // Arrange

  // Act

  // Assert
  TEST_ASSERT_EQUAL_UINT8(1, 2);
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // ModbusDataSplitter tests
  RUN_TEST(test_something);

  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}