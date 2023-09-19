/* defrost: 20, 24, 25 */


#include "esphome/core/log.h"
#include "daalderop.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std; 

namespace esphome
{
  namespace daalderop
  {

    static const char *TAG = "daalderop.sensor";

    void Daalderop::setup()
    {
      // 0x044C: Pump 2 active
      //map_register_to_sensor_and_unit(0x044C, this->pump_p2_active_binary_sensor_, sensorUnit::onOff);

      // 0x04AF: Inside unit ambient temperature
      map_register_to_sensor_and_unit(0x04AF, this->inside_temperature_sensor_, sensorUnit::temperature);

      // 0x04B0: Tb
      map_register_to_sensor_and_unit(0x04B0, this->sanitary_hot_water_temperature_sensor_, sensorUnit::temperature);

      // 0x04B1: Tc
      map_register_to_sensor_and_unit(0x04B1, this->cooling_heating_temperature_sensor_, sensorUnit::temperature);
      
      // 0x04B2: Tuo (outlet temperature)
      map_register_to_sensor_and_unit(0x04B2, this->heat_exchanger_water_outlet_temperature_sensor_, sensorUnit::temperature);
      
      // 0x04B3: Tui (inlet temperature)
      map_register_to_sensor_and_unit(0x04B3, this->heat_exchanger_water_inlet_temperature_sensor_, sensorUnit::temperature);

      // 0x04B4: Tup (condenser temperature)
      map_register_to_sensor_and_unit(0x04B4, this->indoor_coil_temperature_sensor_, sensorUnit::temperature);

      // 0x04B7: Tv1 (heating_circuit_1_temperature)
      map_register_to_sensor_and_unit(0x04B7, this->heating_circuit_1_temperature_sensor_, sensorUnit::temperature);

      // 0x0514: Pump 1 active
      map_register_to_sensor_and_unit(0x0514, this->pump_p1_active_binary_sensor_, sensorUnit::onOff);

      // 0x0834: Outdoor unit voltage
      map_register_to_sensor_and_unit(0x0834, this->outdoor_voltage_sensor_, sensorUnit::voltage);

      // 0x0835: Outdoor unit current
      map_register_to_sensor_and_unit(0x0835, this->outdoor_current_sensor_, sensorUnit::current);

      // 0x0836: Compressor frequency setpoint
      map_register_to_sensor_and_unit(0x0836, this->compressor_working_speed_setpoint_sensor_, sensorUnit::frequency);

      // 0x0837: Actual compressor frequency
      map_register_to_sensor_and_unit(0x0837, this->compressor_working_speed_actual_sensor_, sensorUnit::frequency);

      // 0x0838: Outdoor fan setpoint
      map_register_to_sensor_and_unit(0x0838, this->outdoor_fan_setpoint_sensor_, sensorUnit::frequency);

      // 0x0839: Outdoor fan 1 actual
      map_register_to_sensor_and_unit(0x0839, this->outdoor_fan_1_actual_sensor_, sensorUnit::frequency);

      // 0x083E: Ambient temp
      map_register_to_sensor_and_unit(0x083E, this->outside_temperature_sensor_, sensorUnit::temperature);

      // 0x083F: Tp (outdoor coil temperature)
      map_register_to_sensor_and_unit(0x083F, this->outdoor_coil_temperature_sensor_, sensorUnit::temperature);

      // 0x0840: Td (discharge temperature)
      map_register_to_sensor_and_unit(0x0840, this->discharge_temperature_sensor_, sensorUnit::temperature);

      // 0x0841: Ts (suction temperature)
      map_register_to_sensor_and_unit(0x0841, this->suction_temperature_sensor_, sensorUnit::temperature);

      // 0x0844: Ps (low pressure)
      map_register_to_sensor_and_unit(0x0844, this->low_pressure_sensor_, sensorUnit::pressure);

      // 0x0845: Pd (high pressure)
      map_register_to_sensor_and_unit(0x0845, this->high_pressure_sensor_, sensorUnit::pressure);


      // 0x04BC: Internal pump active
      map_register_to_sensor_and_unit(0x04bc, this->internal_pump_active_binary_sensor_, sensorUnit::onOff);

      // 0x04BE: Heating switch (room thermostat)
      map_register_to_sensor_and_unit(0x04be, this->heating_switch_binary_sensor_, sensorUnit::onOff); 


      // 0x0519: Three way valve (on = heating; off = sanitary hot water)
      map_register_to_sensor_and_unit(0x0519, this->three_way_valve_binary_sensor_, sensorUnit::onOff);

      
      map_register_to_sensor_and_unit(0x083d, this->decode1_binary_sensor_, sensorUnit::onOff); 
      map_register_to_sensor_and_unit(0x0846, this->decode2_binary_sensor_, sensorUnit::onOff); 
      map_register_to_sensor_and_unit(0x0847, this->decode3_binary_sensor_, sensorUnit::onOff); 
      
      map_register_to_sensor_and_unit(0x083c, this->decode20_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x083d, this->decode21_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0842, this->decode22_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0843, this->decode23_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0846, this->decode24_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0847, this->decode25_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0848, this->decode26_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0849, this->decode27_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084A, this->decode28_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084B, this->decode29_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084C, this->decode30_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084D, this->decode31_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084E, this->decode32_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x084F, this->decode33_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0850, this->decode34_sensor_, sensorUnit::frequency);

      map_register_to_sensor_and_unit(0x04bb, this->decode120_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04bd, this->decode121_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04bf, this->decode122_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c0, this->decode123_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c1, this->decode124_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c2, this->decode125_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c3, this->decode126_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c4, this->decode127_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c5, this->decode128_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c6, this->decode129_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c7, this->decode130_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c8, this->decode131_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04c9, this->decode132_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04ca, this->decode133_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x04cb, this->decode134_sensor_, sensorUnit::frequency);

      map_register_to_sensor_and_unit(0x0513, this->decode201_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0515, this->decode202_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0516, this->decode203_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0517, this->decode204_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0518, this->decode205_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x051A, this->decode207_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x051B, this->decode208_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x051C, this->decode209_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x051D, this->decode210_sensor_, sensorUnit::frequency); //Internal heating element
      map_register_to_sensor_and_unit(0x051E, this->decode211_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x051F, this->decode212_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0520, this->decode213_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0521, this->decode214_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0522, this->decode215_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0523, this->decode216_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0524, this->decode217_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0525, this->decode218_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0526, this->decode219_sensor_, sensorUnit::frequency);

      map_register_to_sensor_and_unit(0x044B, this->decode301_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x044C, this->decode302_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x044D, this->decode303_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x044E, this->decode304_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x044F, this->decode305_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0450, this->decode306_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0451, this->decode307_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0452, this->decode308_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0453, this->decode309_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0454, this->decode310_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0455, this->decode311_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0456, this->decode312_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0457, this->decode313_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0458, this->decode314_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x0459, this->decode315_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x045A, this->decode316_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x045B, this->decode317_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x045C, this->decode318_sensor_, sensorUnit::frequency);
      map_register_to_sensor_and_unit(0x045D, this->decode319_sensor_, sensorUnit::frequency);      
      map_register_to_sensor_and_unit(0x045E, this->decode320_sensor_, sensorUnit::frequency);      

    }

    void Daalderop::map_register_to_sensor_and_unit(uint16_t registerNr, sensor::Sensor *sensor, sensorUnit unit) {
      SensorAndUnit sAndU;
      sAndU.sensor.sensor = sensor;
      sAndU.unit = unit;
      registerToSensorAndUnitMap[registerNr] = sAndU;
    }

    void Daalderop::map_register_to_sensor_and_unit(uint16_t registerNr, binary_sensor::BinarySensor *sensor, sensorUnit unit) {
      SensorAndUnit sAndU;
      sAndU.sensor.binarySensor = sensor;
      sAndU.unit = unit;
      registerToSensorAndUnitMap[registerNr] = sAndU;
    }

    void Daalderop::loop()
    {
      const uint32_t now = millis();

      if (now - this->last_modbus_byte_ > 5)
      {
        if (this->rx_buffer_.size() > 0)
        {
          ESP_LOGV(TAG, "Buffer cleared because of timeout");
          this->rx_buffer_.clear();
          this->last_modbus_byte_ = now;
        }
      }

      while (this->available())
      {
        uint8_t byte;
        this->read_byte(&byte);
        if (this->parse_modbus_byte_(byte))
        {
          // Still filling the buffer
          this->last_modbus_byte_ = now;
        }
        else
        {
          // Message complete, clear the buffer
          this->rx_buffer_.clear();
        }
      }
    }

    bool Daalderop::parse_modbus_byte_(uint8_t byte)
    {
      size_t at = this->rx_buffer_.size();
      this->rx_buffer_.push_back(byte);
      const uint8_t *raw = &this->rx_buffer_[0];

      // Byte 0: modbus address (match all)
      if (at == 0)
        return true;
 
      if (at == 7)
      {
        // Check CRC, if valid, the message was a request
        uint16_t computed_crc = crc16(raw, 6);
        uint16_t received_crc = uint16_t(raw[6]) | (uint16_t(raw[7]) << 8);

        if (computed_crc == received_crc)
        {
          // Clear buffer for all messages other than function 3
          uint8_t function_code = raw[1];

          if (function_code == 6) {
            uint16_t address = ((this->rx_buffer_[2] << 8) | this->rx_buffer_[3]);
            uint16_t value = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]);

            ESP_LOGD(TAG, "Function 6 received, processing (address: %04X, value: %04X)", address, value);

            return false;
          }

          if (function_code != 3) {
            ESP_LOGD(TAG, "Function %02X received, discarded", function_code);

            // Loop over all bytes in the receive buffer, and print 'em.
            char *stringBuffer = new char[this->rx_buffer_.size() * 2 + 1];
            stringBuffer[this->rx_buffer_.size() * 2] = '\0';
            uint8_t i = 0;
            std::vector<uint8_t>::iterator it = this->rx_buffer_.begin();
            while (it != this->rx_buffer_.end()) {
              uint8_t high_nibble = (*it) >> 4;
              uint8_t low_nibble = (*it) & 0x0F;
              stringBuffer[i * 2] = (high_nibble > 9 ? (high_nibble - 10 + 'A') : high_nibble + '0');
              stringBuffer[i * 2 + 1] = (low_nibble > 9 ? (low_nibble - 10 + 'A') : low_nibble + '0');
              it++;
              i++;
            }
            ESP_LOGD(TAG, "Raw message bytes: %s", stringBuffer);
            delete[] stringBuffer;

            return false;
          }

          uint16_t requestedBytes = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]) * 2;
          ESP_LOGV(TAG, "Request received : %d bytes, address 0x%02X, function 0x%02X, start address 0x%02X%02X, requested bytes %d", this->rx_buffer_.size(), this->rx_buffer_[0], this->rx_buffer_[1], this->rx_buffer_[2], this->rx_buffer_[3], requestedBytes);

          this->last_request_message_.address = this->rx_buffer_[0];
          this->last_request_message_.function = this->rx_buffer_[1];
          this->last_request_message_.start_address = ((this->rx_buffer_[2] << 8) | this->rx_buffer_[3]);
          this->last_request_message_.requested_registers = ((this->rx_buffer_[4] << 8) | this->rx_buffer_[5]);

          // Request message is complete, return false to clear the buffer
          return false;
        }
      }

      // In case of Function 3 the third byte contains the returned bytes
      uint8_t returned_bytes = raw[2];
      if (at == returned_bytes + 5 - 1)
      {
        uint16_t computed_crc = crc16(raw, at - 1);
        uint16_t received_crc = uint16_t(raw[at - 1]) | (uint16_t(raw[at]) << 8);

        if (computed_crc == received_crc)
        {
          ESP_LOGV(TAG, "Response received: %d bytes, address 0x%02X, function 0x%02X, returned bytes %d", this->rx_buffer_.size(), this->rx_buffer_[0], this->rx_buffer_[1], this->rx_buffer_[2]);

          if (this->last_request_message_.address == this->rx_buffer_[0] &&
              this->last_request_message_.function == this->rx_buffer_[1] &&
              this->last_request_message_.requested_registers * 2 == this->rx_buffer_[2])
          {
            ESP_LOGV(TAG, "Response received which can be linked to the previous request!");

            // Loop over all bytes in the receive buffer, and print 'em.
            char *stringBuffer = new char[this->rx_buffer_.size() * 2 + 1];
            stringBuffer[this->rx_buffer_.size() * 2] = '\0';
            uint8_t i = 0;
            std::vector<uint8_t>::iterator it = this->rx_buffer_.begin();
            while (it != this->rx_buffer_.end()) {
              uint8_t high_nibble = (*it) >> 4;
              uint8_t low_nibble = (*it) & 0x0F;
              stringBuffer[i * 2] = (high_nibble > 9 ? (high_nibble - 10 + 'A') : high_nibble + '0');
              stringBuffer[i * 2 + 1] = (low_nibble > 9 ? (low_nibble - 10 + 'A') : low_nibble + '0');
              it++;
              i++;
            }
            ESP_LOGD(TAG, "Raw message bytes (start address = 0x%04X): %s", this->last_request_message_.start_address, stringBuffer);
            delete[] stringBuffer;

            // Read in all received register values.
            // For each, check if we have a sensor for it
            // So we need a mapping from register (uint16_t) to a sensor
            uint16_t currentRegister = this->last_request_message_.start_address;
            for (uint16_t i = 0; i < this->last_request_message_.requested_registers; ++i) {
              std::map<uint16_t, SensorAndUnit>::iterator it = this->registerToSensorAndUnitMap.find(currentRegister);
              if (it != this->registerToSensorAndUnitMap.end()) {
                // Yes, there's a key-value pair in the map!
                ESP_LOGV(TAG, "Register known: 0x%04X", currentRegister);
                sensor::Sensor *pSensor;
                binary_sensor::BinarySensor *pBinarySensor;
                if (it->second.unit == sensorUnit::onOff) {
                  pBinarySensor = it->second.sensor.binarySensor;
                } else {
                  pSensor = it->second.sensor.sensor;
                }
                if (it->second.sensor.sensor != nullptr) {
                  // Get the value from the response
                  ESP_LOGV(TAG, "Found a sensor matching register 0x%04X", currentRegister);
                  uint16_t registerValue = (this->rx_buffer_[3 + 2 * i] << 8) | this->rx_buffer_[3 + 2 * i + 1];
                  RegisterValueConversion conversionFunction;
                  switch (it->second.unit) {
                    case sensorUnit::temperature: {
                      conversionFunction = &Daalderop::convertRegisterValueToTemperature;
                      float sensorValue = ((*this).*(conversionFunction))(registerValue);
                      ESP_LOGV(TAG, "  Value: %f", sensorValue);
                      pSensor->publish_state(sensorValue);
                      break;
                    }
                    case sensorUnit::pressure:
                    case sensorUnit::current: {
                      conversionFunction = &Daalderop::convertRegisterValueToFloat;
                      float sensorValue = ((*this).*(conversionFunction))(registerValue) / 10.0f;
                      ESP_LOGV(TAG, "  Value: %f", sensorValue);
                      pSensor->publish_state(sensorValue);
                      break;
                    }
                    case sensorUnit::frequency: 
                    case sensorUnit::voltage: {
                      conversionFunction = &Daalderop::convertRegisterValueToFloat;
                      float sensorValue = ((*this).*(conversionFunction))(registerValue);
                      ESP_LOGV(TAG, "  Value: %f", sensorValue);
                      pSensor->publish_state(sensorValue);
                      break;
                    }
                    case sensorUnit::onOff: {
                      bool sensorValue = convertRegisterValueToOnOff(registerValue);
                      ESP_LOGV(TAG, "  Value: " + sensorValue ? "true" : "false");
                      pBinarySensor->publish_state(sensorValue);
                      break;
                    }
                    default:
                      break;
                  }
                }
              }
              ++currentRegister;
            }
          }
          else
          {
            ESP_LOGW(TAG, "Response received which cannot be linked to the previous request!");
            ESP_LOGV(TAG, "  Last stored request:");
            ESP_LOGV(TAG, "    Address             : %02X", this->last_request_message_.address);
            ESP_LOGV(TAG, "    Function            : %02X", this->last_request_message_.function);
            ESP_LOGV(TAG, "    Requested registers : %d", this->last_request_message_.requested_registers);
            ESP_LOGV(TAG, "  Current response:");
            ESP_LOGV(TAG, "    Address             : %02X", this->rx_buffer_[0]);
            ESP_LOGV(TAG, "    Function            : %02X", this->rx_buffer_[1]);
            ESP_LOGV(TAG, "    Requested registers : %d", this->rx_buffer_[2]);
          }

          return false;
        }
      }

      return true;
    }

    float Daalderop::get_setup_priority() const
    {
      // After UART bus
      return setup_priority::BUS - 1.0f;
    }

    void Daalderop::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Daalderop sensor");
      //LOG_SENSOR("  ", "Heat Exchanger Water Outlet Temperature", this->heat_exchanger_water_outlet_temperature_sensor_);
      //LOG_SENSOR("  ", "Heat Exchanger Water Inlet Temperature", this->heat_exchanger_water_inlet_temperature_sensor_);
      //LOG_SENSOR("  ", "Compressor Working Speed", this->compressor_working_speed_sensor_);
    }

  } // namespace empty_compound_sensor
} // namespace daalderop