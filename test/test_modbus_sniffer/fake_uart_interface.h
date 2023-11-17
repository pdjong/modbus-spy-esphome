#ifndef FAKE_UART_INTERFACE_H_
#define FAKE_UART_INTERFACE_H_

#include <queue>
// #include <vector>

// #include <Arduino.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// #include <mbus_reader.h>
// #include <test_includes.h>
#include <uart_interface.h>

// using std::vector;
using std::queue;

class FakeUartInterface : public esphome::modbus_spy::IUartInterface {
  public:
    virtual bool read_byte(uint8_t* data) {
      if (0 == this->fake_data_to_return_.size()) {
        return false;
      } else {
        *data = this->fake_data_to_return_.front();
        this->fake_data_to_return_.pop();
        return true;
      }
    }

    virtual bool read_array(uint8_t* data, size_t len) {
      for (size_t i = 0; i < len; ++i) {
        if (this->fake_data_to_return_.empty()) {
          break;
        } else {
          *data++ = this->fake_data_to_return_.front();
          this->fake_data_to_return_.pop();
        }
      }
      return true;
    }

    virtual int available() const {
      return this->fake_data_to_return_.size();
    }

    // Access / configure methods
    void set_fake_data_to_return(const uint8_t* fake_data, size_t len) {
      for (size_t i = 0; i < len; ++i) {
        this->fake_data_to_return_.push(fake_data[i]);
      }
    }

  protected:
    queue<uint8_t> fake_data_to_return_;
};

// typedef struct FakeUartInterfaceTaskArgs {
//   FakeUartInterface* uart_interface;
//   const uint8_t respond_to_nth_write;
//   const uint8_t delay_in_ms;
//   const uint8_t* data_to_return;
//   const size_t len_of_data_to_return;
// } FakeUartInterfaceTaskArgs;

// void fake_uart_interface_task(void* param) {
//   FakeUartInterfaceTaskArgs *args = reinterpret_cast<FakeUartInterfaceTaskArgs*>(param);
//   FakeUartInterface *uart_interface = args->uart_interface;
//   while (uart_interface->write_array_call_count() < args->respond_to_nth_write) {
//     vTaskDelay(1 / portTICK_PERIOD_MS);
//   }
//   delay(args->delay_in_ms);
//   uart_interface->set_fake_data_to_return(args->data_to_return, args->len_of_data_to_return);
//   vTaskDelete(NULL);
// }

#endif // FAKE_UART_INTERFACE_H_