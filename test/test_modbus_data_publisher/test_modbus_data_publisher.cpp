#include <vector>

#include <Arduino.h>
#include <unity.h>

#include "fake_modbus_binary_sensor.h"
#include "fake_modbus_register_sensor.h"
#include "modbus_data.h"
#include <test_includes.h>
#include "testable_modbus_data_publisher.h"

using std::vector;
using namespace esphome::modbus_spy;

void assert_binary_sensor_for_bit(FakeModbusBinarySensor* sensor, uint8_t bit, uint16_t value);

void test_add_register_sensor_and_find_same_sensor_returns_sensor() {
  // Arrange
  TestableModbusDataPublisher data_publisher;
  FakeModbusRegisterSensor *fake_register_sensor = new FakeModbusRegisterSensor;

  // Act
  data_publisher.add_register_sensor(0x01, 0x1234, fake_register_sensor);
  IModbusRegisterSensor *found_register_sensor = data_publisher.call_find_register_sensor(0x01, 0x1234);

  // Assert
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor, found_register_sensor);
}

void test_add_register_sensor_and_find_for_different_device_returns_nullptr() {
  // Arrange
  TestableModbusDataPublisher data_publisher;
  FakeModbusRegisterSensor *fake_register_sensor = new FakeModbusRegisterSensor;

  // Act
  data_publisher.add_register_sensor(0x01, 0x1234, fake_register_sensor);
  IModbusRegisterSensor *found_register_sensor = data_publisher.call_find_register_sensor(0x02, 0x1234);

  // Assert
  TEST_ASSERT_NULL(found_register_sensor);
}

void test_add_register_sensor_and_find_for_different_register_address_returns_nullptr() {  
  // Arrange
  TestableModbusDataPublisher data_publisher;
  FakeModbusRegisterSensor *fake_register_sensor = new FakeModbusRegisterSensor;

  // Act
  data_publisher.add_register_sensor(0x01, 0x1234, fake_register_sensor);
  IModbusRegisterSensor *found_register_sensor = data_publisher.call_find_register_sensor(0x01, 0x1235);

  // Assert
  TEST_ASSERT_NULL(found_register_sensor);
}

void test_add_multiple_register_sensors_same_register_address_different_devices_find_returns_correct_sensor() {
  // Arrange
  TestableModbusDataPublisher data_publisher;
  FakeModbusRegisterSensor *fake_register_sensor1 = new FakeModbusRegisterSensor;
  FakeModbusRegisterSensor *fake_register_sensor2 = new FakeModbusRegisterSensor;

  // Act
  data_publisher.add_register_sensor(0x01, 0x1234, fake_register_sensor1);
  data_publisher.add_register_sensor(0x02, 0x1234, fake_register_sensor2);
  IModbusRegisterSensor *found_register_sensor2 = data_publisher.call_find_register_sensor(0x02, 0x1234);
  IModbusRegisterSensor *found_register_sensor1 = data_publisher.call_find_register_sensor(0x01, 0x1234);

  // Assert
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor1, found_register_sensor1);
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor2, found_register_sensor2);
}

void test_add_multiple_register_sensors_multiple_per_device_find_returns_correct_sensor() {
  // Arrange
  TestableModbusDataPublisher data_publisher;
  FakeModbusRegisterSensor *fake_register_sensor_device1_reg_addr1 = new FakeModbusRegisterSensor;
  FakeModbusRegisterSensor *fake_register_sensor_device1_reg_addr2 = new FakeModbusRegisterSensor;
  FakeModbusRegisterSensor *fake_register_sensor_device2_reg_addr1 = new FakeModbusRegisterSensor;
  FakeModbusRegisterSensor *fake_register_sensor_device2_reg_addr2 = new FakeModbusRegisterSensor;

  // Act
  data_publisher.add_register_sensor(0x01, 0x0A01, fake_register_sensor_device1_reg_addr1);
  data_publisher.add_register_sensor(0x01, 0x0A02, fake_register_sensor_device1_reg_addr2);
  data_publisher.add_register_sensor(0x02, 0x0A01, fake_register_sensor_device2_reg_addr1);
  data_publisher.add_register_sensor(0x02, 0x0A02, fake_register_sensor_device2_reg_addr2);
  IModbusRegisterSensor *found_register_sensor_device1_reg_addr1 = data_publisher.call_find_register_sensor(0x01, 0x0A01);
  IModbusRegisterSensor *found_register_sensor_device1_reg_addr2 = data_publisher.call_find_register_sensor(0x01, 0x0A02);
  IModbusRegisterSensor *found_register_sensor_device2_reg_addr1 = data_publisher.call_find_register_sensor(0x02, 0x0A01);
  IModbusRegisterSensor *found_register_sensor_device2_reg_addr2 = data_publisher.call_find_register_sensor(0x02, 0x0A02);

  // Assert
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor_device1_reg_addr1, found_register_sensor_device1_reg_addr1);
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor_device1_reg_addr2, found_register_sensor_device1_reg_addr2);
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor_device2_reg_addr1, found_register_sensor_device2_reg_addr1);
  TEST_ASSERT_EQUAL_PTR(fake_register_sensor_device2_reg_addr2, found_register_sensor_device2_reg_addr2);
}

void test_publish_data_function_3() {
  // Arrange
  const uint8_t device_address = 0x02;
  const int8_t function = 3;
  const uint16_t register_address = 0x01AF;
  const uint16_t register_value = 0x3210;
  ModbusDataPublisher data_publisher;
  vector<ModbusData*> *data = new vector<ModbusData*>;
  ModbusData *modbus_data = new ModbusData;
  modbus_data->address = register_address;
  modbus_data->value = 0x3210;
  data->push_back(modbus_data);

  FakeModbusRegisterSensor *fakeRegisterSensor = new FakeModbusRegisterSensor;
  data_publisher.add_register_sensor(device_address, register_address + 40001, fakeRegisterSensor);

  // Act
  data_publisher.publish_data(device_address, function, data);

  // Assert
  vector<uint16_t> *published_states = fakeRegisterSensor->get_published_states();
  TEST_ASSERT_EQUAL_UINT8(1, published_states->size());
  uint16_t expected_value = register_value;
  uint16_t actual_value = published_states->at(0);
  TEST_ASSERT_EQUAL_UINT16(expected_value, actual_value);
}

void test_publish_data_binary_flag_sensors() {
  // Arrange
  const uint8_t device_address = 0x02;
  const int8_t function = 3;
  const uint16_t register_address = 0x01AF;
  const uint16_t register_value = 0b1100111010001110;
  ModbusDataPublisher data_publisher;
  vector<ModbusData*> *data = new vector<ModbusData*>;
  ModbusData *modbus_data = new ModbusData;
  modbus_data->address = register_address;
  modbus_data->value = register_value;
  data->push_back(modbus_data);

  FakeModbusBinarySensor *fakeBinarySensorBit0 = new FakeModbusBinarySensor;
  data_publisher.add_binary_sensor(device_address, register_address + 40001, 0, fakeBinarySensorBit0);
  FakeModbusBinarySensor *fakeBinarySensorBit1 = new FakeModbusBinarySensor;
  data_publisher.add_binary_sensor(device_address, register_address + 40001, 1, fakeBinarySensorBit0);
  FakeModbusBinarySensor *fakeBinarySensorBit15 = new FakeModbusBinarySensor;
  data_publisher.add_binary_sensor(device_address, register_address + 40001, 15, fakeBinarySensorBit0);

  // Act
  data_publisher.publish_data(device_address, function, data);

  // Assert
  assert_binary_sensor_for_bit(fakeBinarySensorBit0, 0, register_value);
  assert_binary_sensor_for_bit(fakeBinarySensorBit1, 1, register_value);
  assert_binary_sensor_for_bit(fakeBinarySensorBit15, 15, register_value);
}

void assert_binary_sensor_for_bit(FakeModbusBinarySensor* sensor, uint8_t bit, uint16_t register_value) {
  vector<bool> *published_states = sensor->get_published_states();
  TEST_ASSERT_EQUAL_UINT8(1, published_states->size());
  bool expected_value = (register_value & (1 << 0)) >> 0;
  bool actual_value = published_states->at(0);
  if (expected_value) {
    TEST_ASSERT_TRUE(actual_value);
  } else {
    TEST_ASSERT_FALSE(actual_value);
  }
}

int runUnityTests(void) {
  UNITY_BEGIN();

  // add_register_sensor and find_sensor tests
  RUN_TEST(test_add_register_sensor_and_find_same_sensor_returns_sensor);
  RUN_TEST(test_add_register_sensor_and_find_for_different_device_returns_nullptr);
  RUN_TEST(test_add_register_sensor_and_find_for_different_register_address_returns_nullptr);
  RUN_TEST(test_add_multiple_register_sensors_same_register_address_different_devices_find_returns_correct_sensor);
  RUN_TEST(test_add_multiple_register_sensors_multiple_per_device_find_returns_correct_sensor);

  // publish_data tests
  RUN_TEST(test_publish_data_function_3);
  RUN_TEST(test_publish_data_binary_flag_sensors);

  return UNITY_END();
}

void setup() {
  // Wait 2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}