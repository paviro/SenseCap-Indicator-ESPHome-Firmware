#include "json_uart.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"
#include <ArduinoJson.h>
#include <vector>
#include <sstream>

namespace esphome {
namespace json_uart {

static const char *TAG = "json_uart.sensor";
std::string json_data;


void JsonUartSensor::setup() {
}

void JsonUartSensor::loop() {
  // Read JSON data from UART
  std::string raw_data;
  while (this->available()) {
    uint8_t c;
    this->read_byte(&c);
    if (c == '\n') {
      // Store the latest line
      json_data = raw_data;
      raw_data.clear();  // Clear the buffer after storing the line
    } else {
      raw_data += static_cast<char>(c);  // Cast to char before appending
    }
  }
}

void JsonUartSensor::update() {
  if (json_data.empty()) {
    ESP_LOGW(TAG, "No data received from UART yet");
    return;
  }

  ESP_LOGD(TAG, "Updating sensor with JSON data: %s", json_data.c_str());
  parse_json_data(json_data);
}

void JsonUartSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "JSON UART custom sensor");
  ESP_LOGCONFIG(TAG, "  Key: %s", key_.c_str());
  ESP_LOGCONFIG(TAG, "  Unit of Measurement: %s", unit_of_measurement_.c_str());
}

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void JsonUartSensor::parse_json_data(const std::string &json_data) {
  // Parse the JSON data and extract the value for the given key
  ESP_LOGD(TAG, "Parsing JSON data: %s", json_data.c_str());
  StaticJsonDocument<1024> doc;
  auto error = deserializeJson(doc, json_data);
  if (error) {
    ESP_LOGW(TAG, "Failed to parse JSON data: %s", error.c_str());
    return;
  }

  JsonObject root = doc.as<JsonObject>();
  std::vector<std::string> keys = split(key_, '.');
  JsonObject current = root;
  for (size_t i = 0; i < keys.size(); ++i) {
    if (!current[keys[i].c_str()].is<JsonObject>() && i != keys.size() - 1) {
      ESP_LOGW(TAG, "Key %s not found in JSON data", key_.c_str());
      return;
    }
    if (i == keys.size() - 1) {
      if (!current[keys[i].c_str()].is<float>()) {
        ESP_LOGW(TAG, "Key %s does not contain a float value", key_.c_str());
        return;
      }
      float value = current[keys[i].c_str()].as<float>();
      ESP_LOGD(TAG, "Parsed value for key %s: %f", key_.c_str(), value);
      this->publish_state(value);
    } else {
      current = current[keys[i].c_str()].as<JsonObject>();
    }
  }
}

}  // namespace json_uart
}  // namespace esphome
