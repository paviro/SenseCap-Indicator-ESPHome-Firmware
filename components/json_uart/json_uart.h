#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"  // Correct header for UARTDevice

namespace esphome {
namespace json_uart {

class JsonUartSensor : public sensor::Sensor, public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;
  void set_key(const std::string &key) { key_ = key; }
  void set_unit_of_measurement(const std::string &unit) { unit_of_measurement_ = unit; }

 protected:
  std::string key_;
  std::string unit_of_measurement_;
  void parse_json_data(const std::string &json_data);
};

}  // namespace json_uart
}  // namespace esphome
