#include <iostream>
#include <vector>
#include <sstream>

#include <Arduino.h>
#include "esphome/core/log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "modbus_sniffer.h"
#include "modbus_frame.h"

using namespace std; 

namespace esphome {
namespace modbus_spy {

static const char *TAG = "ModbusSniffer";

void ModbusSniffer::start_sniffing()
{
  xTaskCreatePinnedToCore(ModbusSniffer::sniff_loop_task,
                              "sniff_task", // name
                              30000,        // stack size (in words)
                              this,         // input params
                              1,            // priority
                              nullptr,      // Handle, not needed
                              0             // core
  );
}

void ModbusSniffer::sniff_loop_task(void* params) {
  ModbusSniffer *modbus_sniffer = reinterpret_cast<ModbusSniffer*>(params);
  while (true) {
    //  1. Wait for incoming data
    //  2. Receive entire request
    //  3. If not a request, discard the data, empty the entire receive buffer and start over
    //  4. It is a request, so wait for incoming data
    //  5. Receive entire response
    //  6. If not a response, discard the data, empty the entire receive buffer and start over
    //  7. It is a response! Check if it matches the request
    //  8. If the response does not match the request, start over
    //     The response matches the request!
    //  9. Handle the data

    // 1. Wait for incoming data
    // while (modbus_sniffer->available() == 0) {
    //   delayMicroseconds(500);
    // }

    // // 2. Receive entire request
    // const ModbusFrame *request = modbus_sniffer->receive_request();

    // // 3. If not a request, discard the data, empty the entire receive buffer and start over
    // if (nullptr == request) {
    //   // TODO
    //   continue;
    // }

    // // 4. It is a request, so wait for incoming data
    // while (modbus_sniffer->available() == 0) {
    //   delayMicroseconds(500);
    // }

    // // 5. Receive entire response
    // const ModbusResponse response = modbus_sniffer->receive_response();

    // // 6. If not a response, discard the data, empty the entire receive buffer and start over
    // if (nullptr == response) {
    //   // TODO
    //   continue;
    // }

    // // 7. It is a response! Check if it matches the request
    // const bool response_matches_request = modbus_sniffer->does_response_match_request(response, request);

    // // 8. If the response does not match the request, start over
    // if (!response_matches_request) {
    //   // TODO
    //   continue;
    // }

    // // The response matches the request! Check if we're interested in the data:
    // // 9. Handle the data
    // modbus_sniffer->handle_data_in_request_response(request, response);
    
    delay(1);
  }
}

// void ModbusSpy::fleppertje() {
//   bool current_package_done = false;
//   bool first_byte = true;
//   while (!current_package_done) {
//     while (this->available() == 0) {
//       delayMicroseconds(125);
//     }
//     uint32_t now = millis();

//     if (!first_byte && (now - this->last_modbus_byte_ > 500))
//     {
//       if (this->rx_buffer_.size() > 0)
//       {
//         ESP_LOGV(TAG, "Buffer cleared because of timeout. RX buffer follows, with all available() bytes");

//         // ESP_LOGV(TAG, "(Appending %d bytes in UART buffer)", this->available());
//         // while (this->available())
//         // {
//         //   uint8_t byte;
//         //   this->read_byte(&byte);
//         //   this->rx_buffer_.push_back(byte);
//         // }

//         this->log_rx_buffer();
//         this->rx_buffer_.clear();
//         this->last_modbus_byte_ = now;
//         current_package_done = true;
//       }
//       while (this->available())
//       {
//         uint8_t byte;
//         this->read_byte(&byte);

//       }
//       break;
//     }
//     first_byte = false;

//     while (this->available())
//     {
//       uint8_t byte;
//       this->read_byte(&byte);
//       now = millis();
//       if (this->parse_modbus_byte_(byte))
//       {
//         // Still filling the buffer
//         this->last_modbus_byte_ = now;
//         current_package_done = false;
//       }
//       else
//       {
//         // Message complete, clear the buffer
//         this->rx_buffer_.clear();
//         current_package_done = true;
//         break;
//       }
//     }
//   }
// }

// void ModbusSniffer::log_rx_buffer() {
//   char *string_buffer = new char[this->rx_buffer_.size() * 2 + 1];
//   string_buffer[this->rx_buffer_.size() * 2] = '\0';
  
//   size_t i { 0 };
//   for (auto rx_byte : this->rx_buffer_) {
//     uint8_t high_nibble = rx_byte >> 4;
//     uint8_t low_nibble = rx_byte & 0x0F;
//     string_buffer[i * 2] = (high_nibble > 9 ? (high_nibble - 10 + 'A') : high_nibble + '0');
//     string_buffer[i * 2 + 1] = (low_nibble > 9 ? (low_nibble - 10 + 'A') : low_nibble + '0');
//     ++i;
//   }
//   ESP_LOGD(TAG, "Raw message bytes (count = %d): %s", this->rx_buffer_.size(), string_buffer);
//   delete[] string_buffer;
// }


// bool ModbusSpy::parse_modbus_byte_(uint8_t byte)
// {
//   size_t at = this->rx_buffer_.size();
//   this->rx_buffer_.push_back(byte);
//   const uint8_t *raw = &this->rx_buffer_[0];

//   // Byte 0: modbus address (match all)
//   if (at == 0)
//     return true;

//   if (at == 7)
//   {
//     // Check CRC, if valid, the message was a request
//     uint16_t computed_crc = crc16(raw, 6);
//     uint16_t received_crc = uint16_t(raw[6]) | (uint16_t(raw[7]) << 8);

//     if (computed_crc == received_crc)
//     {
//       // Clear buffer for all messages other than function 3
//       uint8_t function_code = raw[1];

//       if (function_code == 6) {
//         uint16_t address = ((this->rx_buffer_[2] << 8) | this->rx_buffer_[3]);
//         uint16_t value = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]);

//         ESP_LOGD(TAG, "Function 6 received, processing (address: %04X, value: %04X)", address, value);

//         return false;
//       }

//       if (function_code != 3) {
//         ESP_LOGD(TAG, "Function %02X received, discarded", function_code);

//         // Loop over all bytes in the receive buffer, and print 'em.
//         this->log_rx_buffer();

//         return false;
//       }

//       uint16_t requestedBytes = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]) * 2;
//       ESP_LOGV(TAG, "Request received : %d bytes, address 0x%02X, function 0x%02X, start address 0x%02X%02X, requested bytes %d", this->rx_buffer_.size(), this->rx_buffer_[0], this->rx_buffer_[1], this->rx_buffer_[2], this->rx_buffer_[3], requestedBytes);

//       this->last_request_message_.address = this->rx_buffer_[0];
//       this->last_request_message_.function = this->rx_buffer_[1];
//       this->last_request_message_.start_address = ((this->rx_buffer_[2] << 8) | this->rx_buffer_[3]);
//       this->last_request_message_.requested_registers = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]);

//       // Request message is complete, return false to clear the buffer
//       return false;
//     }
//   }

//   // In case of Function 3 the third byte contains the returned bytes
//   uint8_t returned_bytes = raw[2];
//   if (at == returned_bytes + 5 - 1)
//   {
//     uint16_t computed_crc = crc16(raw, at - 1);
//     uint16_t received_crc = uint16_t(raw[at - 1]) | (uint16_t(raw[at]) << 8);

//     if (computed_crc == received_crc)
//     {
//       ESP_LOGV(TAG, "Response received: %d bytes, address 0x%02X, function 0x%02X, returned bytes %d", this->rx_buffer_.size(), this->rx_buffer_[0], this->rx_buffer_[1], this->rx_buffer_[2]);

//       if (this->last_request_message_.address == this->rx_buffer_[0] &&
//           this->last_request_message_.function == this->rx_buffer_[1] &&
//           this->last_request_message_.requested_registers * 2 == this->rx_buffer_[2])
//       {
//         ESP_LOGV(TAG, "Response received which can be linked to the previous request!");

//         // Loop over all bytes in the receive buffer, and print 'em.
//         char *stringBuffer = new char[this->rx_buffer_.size() * 2 + 1];
//         stringBuffer[this->rx_buffer_.size() * 2] = '\0';
//         uint8_t i = 0;
//         std::vector<uint8_t>::iterator it = this->rx_buffer_.begin();
//         while (it != this->rx_buffer_.end()) {
//           uint8_t high_nibble = (*it) >> 4;
//           uint8_t low_nibble = (*it) & 0x0F;
//           stringBuffer[i * 2] = (high_nibble > 9 ? (high_nibble - 10 + 'A') : high_nibble + '0');
//           stringBuffer[i * 2 + 1] = (low_nibble > 9 ? (low_nibble - 10 + 'A') : low_nibble + '0');
//           it++;
//           i++;
//         }
//         ESP_LOGD(TAG, "Raw message bytes (start address = 0x%04X): %s", this->last_request_message_.start_address, stringBuffer);
//         delete[] stringBuffer;

//         // Read in all received register values.
//         // For each, check if we have a sensor for it
//         // So we need a mapping from register (uint16_t) to a sensor
//         uint16_t currentRegister = this->last_request_message_.start_address;
//         for (uint16_t i = 0; i < this->last_request_message_.requested_registers; ++i) {
//           std::map<uint16_t, SensorAndUnit>::iterator it = this->registerToSensorAndUnitMap.find(currentRegister);
//           if (it != this->registerToSensorAndUnitMap.end()) {
//             // Yes, there's a key-value pair in the map!
//             ESP_LOGV(TAG, "Register known: 0x%04X", currentRegister);
//             sensor::Sensor *pSensor;
//             binary_sensor::BinarySensor *pBinarySensor;
//             if (it->second.unit == sensorUnit::onOff) {
//               pBinarySensor = it->second.sensor.binarySensor;
//             } else {
//               pSensor = it->second.sensor.sensor;
//             }
//             if (it->second.sensor.sensor != nullptr) {
//               // Get the value from the response
//               ESP_LOGV(TAG, "Found a sensor matching register 0x%04X", currentRegister);
//               uint16_t registerValue = (this->rx_buffer_[3 + 2 * i] << 8) | this->rx_buffer_[3 + 2 * i + 1];
//               RegisterValueConversion conversionFunction;
//               switch (it->second.unit) {
//                 case sensorUnit::temperature: {
//                   conversionFunction = &ModbusSpy::convertRegisterValueToTemperature;
//                   float sensorValue = ((*this).*(conversionFunction))(registerValue);
//                   ESP_LOGV(TAG, "  Value: %f", sensorValue);
//                   pSensor->publish_state(sensorValue);
//                   break;
//                 }
//                 case sensorUnit::pressure:
//                 case sensorUnit::current: {
//                   conversionFunction = &ModbusSpy::convertRegisterValueToFloat;
//                   float sensorValue = ((*this).*(conversionFunction))(registerValue) / 10.0f;
//                   ESP_LOGV(TAG, "  Value: %f", sensorValue);
//                   pSensor->publish_state(sensorValue);
//                   break;
//                 }
//                 case sensorUnit::frequency: 
//                 case sensorUnit::voltage: {
//                   conversionFunction = &ModbusSpy::convertRegisterValueToFloat;
//                   float sensorValue = ((*this).*(conversionFunction))(registerValue);
//                   ESP_LOGV(TAG, "  Value: %f", sensorValue);
//                   pSensor->publish_state(sensorValue);
//                   break;
//                 }
//                 case sensorUnit::onOff: {
//                   bool sensorValue = convertRegisterValueToOnOff(registerValue);
//                   ESP_LOGV(TAG, "  Value: " + sensorValue ? "true" : "false");
//                   pBinarySensor->publish_state(sensorValue);
//                   break;
//                 }
//                 default:
//                   break;
//               }
//             }
//           }
//           ++currentRegister;
//         }
//       }
//       else
//       {
//         ESP_LOGW(TAG, "Response received which cannot be linked to the previous request!");
//         ESP_LOGV(TAG, "  Last stored request:");
//         ESP_LOGV(TAG, "    Address             : %02X", this->last_request_message_.address);
//         ESP_LOGV(TAG, "    Function            : %02X", this->last_request_message_.function);
//         ESP_LOGV(TAG, "    Requested registers : %d", this->last_request_message_.requested_registers);
//         ESP_LOGV(TAG, "  Current response:");
//         ESP_LOGV(TAG, "    Address             : %02X", this->rx_buffer_[0]);
//         ESP_LOGV(TAG, "    Function            : %02X", this->rx_buffer_[1]);
//         ESP_LOGV(TAG, "    Requested registers : %d", this->rx_buffer_[2]);
//       }

//       return false;
//     }
//   }

//   return true;
// }


} // namespace modbus_spy
} // namespace esphome