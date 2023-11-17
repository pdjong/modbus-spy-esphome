#include <Arduino.h>
#ifdef UNIT_TEST
#include "test_includes.h"
#else
#include "esphome/core/datatypes.h"
#include "esphome/core/helpers.h"
#endif

#include "modbus_frame.h"
#include "modbus_request_detector.h"

namespace esphome {
namespace modbus_spy {

ModbusFrame* ModbusRequestDetector::detect_request() {
	//  1. Read the first byte. Assume it is the address
	//  2. Read the second byte. Assume it is the function
	//  If function 1-6:
	//  	○ Read six more bytes
	//  	○ See if the last two bytes contain the correct CRC
	//  	○ If so, it is a request. If not, it is not a request.
	//  If function 15-16:
	//  	○ Read five more bytes
	//  	○ Last byte is the number of data bytes to follow.
	//  	○ Read this number of bytes, + 2 extra
	//  	○ See if the last two bytes contain the correct CRC
	//  	○ If so, it is a request. If not, it is not a request.
  while (this->uart_interface_->available() == 0);
  this->time_last_byte_received_ = millis();
  uint8_t address { 0 };
  if (!read_next_byte(&address)) {
    return nullptr;
  }
  uint8_t function { 0 };
  if (!read_next_byte(&function)) {
    return nullptr;
  }

  if ((function >= 1) && (function <= 6)) {
    uint8_t *raw_data = new uint8_t[6];
    raw_data[0] = address;
    raw_data[1] = function;
    for (uint8_t i { 2 }; i < 6; ++i) {
      if (!read_next_byte(&raw_data[i])) {
        delete[] raw_data;
        return nullptr;
      }
    }
    uint8_t crc_low_byte { 0x00 };
    if (!read_next_byte(&crc_low_byte)) {
      delete[] raw_data;
      return nullptr;
    }
    uint8_t crc_high_byte { 0x00 };
    if (!read_next_byte(&crc_high_byte)) {
      delete[] raw_data;
      return nullptr;
    }
    uint16_t calculated_crc = crc16(raw_data, 6);
    uint16_t received_crc = crc_low_byte | (crc_high_byte << 8);
    if (calculated_crc != received_crc) {
      delete[] raw_data;
      return nullptr;
    }
    // CRC is right! So this must be a request.
    uint8_t *data = new uint8_t[4];
    for (uint8_t i {0}; i < 4; ++i) {
      data[i] = raw_data[i + 2];
    }
    delete[] raw_data;
    ModbusFrame *request_frame = new ModbusFrame(address, function, data, 4);
    return request_frame;
  } else if ((function >= 15) && (function <= 16)) {
  } else {
    // Unsupported function!
    return nullptr;
  }

  return nullptr;
}

bool ModbusRequestDetector::read_next_byte(uint8_t* byte) {
  if (this->uart_interface_->available() == 0) {
    // Next byte didn't arrive yet. Wait for it, with a timeout.
    bool waiting_too_long { false };
    do {
      delayMicroseconds(100);
      waiting_too_long = (millis() - this->time_last_byte_received_) > MAX_TIME_BETWEEN_BYTES_IN_MS;
    } while ((this->uart_interface_->available() == 0) && !waiting_too_long);
    if (this->uart_interface_->available() == 0) {
      // Still nothing after waiting, so no byte in time...
      return false;
    }
  }
  bool is_byte_received = this->uart_interface_->read_byte(byte);
  if (is_byte_received) {
    this->time_last_byte_received_ = millis();
  }
  return is_byte_received;
}

} //namespace modbus_spy
} //namespace esphome
