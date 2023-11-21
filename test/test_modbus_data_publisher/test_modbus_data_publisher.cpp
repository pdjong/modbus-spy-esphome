#include <vector>

#include <Arduino.h>
#include <unity.h>

#include "fake_modbus_register_sensor.h"
#include "modbus_data.h"
#include "modbus_data_publisher.h"
#include <test_includes.h>

using std::vector;
using namespace esphome::modbus_spy;

void test_publish_data_function_3() {
  // Arrange
  const uint8_t device_address = 0x02;
  const int8_t function = 3;
  const uint16_t register_address = 0x01AF;
  const uint16_t register_value = 0x3210;
  ModbusDataPublisher data_publisher;
  vector<ModbusData*> *data = new vector<ModbusData*>;
  ModbusData modbus_data;
  modbus_data.address = register_address;
  modbus_data.value = 0x3210;
  data->push_back(&modbus_data);

  FakeModbusRegisterSensor fakeRegisterSensor;
  data_publisher.add_register_sensor(device_address, register_address + 40001, &fakeRegisterSensor);

  // Act
  data_publisher.publish_data(device_address, function, data);

  // Assert
  vector<uint16_t> *published_states = fakeRegisterSensor.get_published_states();
  TEST_ASSERT_EQUAL_UINT8(1, published_states->size());
  uint16_t expected_value = register_value;
  uint16_t actual_value = published_states->at(0);
  TEST_ASSERT_EQUAL_UINT16(expected_value, actual_value);
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // ModbusDataPublisher tests
  RUN_TEST(test_publish_data_function_3);

  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}