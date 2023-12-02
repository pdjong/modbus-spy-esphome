#include "fake_modbus_binary_sensor.h"

FakeModbusBinarySensor::~FakeModbusBinarySensor() {
}

void FakeModbusBinarySensor::publish_state(bool state) {
  this->published_states_.push_back(state);
}

vector<bool>* FakeModbusBinarySensor::get_published_states() {
  return &this->published_states_;
}