#include "apc1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace apc1 {

static const char *const TAG = "apc1";

void APC1Component::setup() {
  // Set to passive mode to match PollingComponent behavior
  const uint8_t set_passive[] = {0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70};
  this->write_array(set_passive, sizeof(set_passive));
}

void APC1Component::update() {
  // Request measurement
  const uint8_t request_measurement[] = {0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71};
  this->write_array(request_measurement, sizeof(request_measurement));
}

void APC1Component::dump_config() {
  ESP_LOGCONFIG(TAG, "APC1:");
  LOG_SENSOR("  ", "PM1.0", this->pm_1_0_sensor_);
  LOG_SENSOR("  ", "PM2.5", this->pm_2_5_sensor_);
  LOG_SENSOR("  ", "PM10.0", this->pm_10_0_sensor_);
  LOG_SENSOR("  ", "PM1.0 in air", this->pm_1_0_in_air_sensor_);
  LOG_SENSOR("  ", "PM2.5 in air", this->pm_2_5_in_air_sensor_);
  LOG_SENSOR("  ", "PM10.0 in air", this->pm_10_0_in_air_sensor_);
  LOG_SENSOR("  ", "PM0.3um", this->pm_particles_0_3um_sensor_);
  LOG_SENSOR("  ", "PM0.5um", this->pm_particles_0_5um_sensor_);
  LOG_SENSOR("  ", "PM1.0um", this->pm_particles_1_0um_sensor_);
  LOG_SENSOR("  ", "PM2.5um", this->pm_particles_2_5um_sensor_);
  LOG_SENSOR("  ", "PM5.0um", this->pm_particles_5_0um_sensor_);
  LOG_SENSOR("  ", "PM10.0um", this->pm_particles_10_0um_sensor_);
  LOG_SENSOR("  ", "RS0", this->rs0_sensor_);
  LOG_SENSOR("  ", "RS1", this->rs1_sensor_);
  LOG_SENSOR("  ", "RS2", this->rs2_sensor_);
  LOG_SENSOR("  ", "RS3", this->rs3_sensor_);
  LOG_SENSOR("  ", "TVOC", this->tvoc_sensor_);
  LOG_SENSOR("  ", "eCO2", this->eco2_sensor_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "Humidity", this->humidity_sensor_);
  LOG_SENSOR("  ", "Temperature Raw", this->temperature_raw_sensor_);
  LOG_SENSOR("  ", "Humidity Raw", this->humidity_raw_sensor_);
  LOG_SENSOR("  ", "Error Code", this->error_code_sensor_);
  LOG_SENSOR("  ", "AQI", this->aqi_sensor_);
  this->check_uart_settings(9600);
}

void APC1Component::loop() {
  const uint32_t now = millis();

  // Reset receive buffer if the last byte was received too long ago
  if (now - this->last_transmission_ >= 500) {
    this->data_index_ = 0;
  }

  if (this->available() == 0)
    return;

  this->last_transmission_ = now;
  while (this->available() != 0) {
    this->read_byte(&this->data_[this->data_index_]);
    auto check = this->check_byte_();
    if (!check.has_value()) {
      // Packet is complete and valid
      this->parse_data_();
      this->data_index_ = 0;
    } else if (!*check) {
      // Invalid byte or packet
      this->data_index_ = 0;
    } else {
      // Valid byte, wait for next
      this->data_index_++;
    }
  }
}

optional<bool> APC1Component::check_byte_() {
  uint8_t index = this->data_index_;
  uint8_t byte = this->data_[index];

  if (index == 0) return byte == 0x42;
  if (index == 1) return byte == 0x4D;
  if (index == 2) return true;
  if (index == 3) {
    uint16_t payload_length = this->get_16_bit_uint_(2);
    // Payload length for APC1 measurement frame should be 60 bytes
    if (payload_length != 60) {
      ESP_LOGW(TAG, "APC1 Payload length %u doesn't match expected 60.", payload_length);
      return false;
    }
    return true;
  }

  // Total size = 4 (header) + 60 (payload) = 64
  if (index < 63) {
    return true;
  }

  // Calculate checksum for bytes 0 to 61
  uint16_t checksum = 0;
  for (uint16_t i = 0; i < 62; i++) {
    checksum += this->data_[i];
  }

  uint16_t check = this->get_16_bit_uint_(62);
  if (checksum != check) {
    ESP_LOGW(TAG, "APC1 checksum mismatch! Calculated: 0x%04X, Received: 0x%04X", checksum, check);
    return false;
  }

  return {}; // return empty optional to signal successful completion
}

uint16_t APC1Component::get_16_bit_uint_(uint8_t start_index) const {
  return (uint16_t(this->data_[start_index]) << 8) | uint16_t(this->data_[start_index + 1]);
}

uint32_t APC1Component::get_32_bit_uint_(uint8_t start_index) const {
  return (uint32_t(this->data_[start_index]) << 24) |
         (uint32_t(this->data_[start_index + 1]) << 16) |
         (uint32_t(this->data_[start_index + 2]) << 8) |
         uint32_t(this->data_[start_index + 3]);
}

void APC1Component::parse_data_() {
  uint16_t pm_1_0 = this->get_16_bit_uint_(0x04);
  uint16_t pm_2_5 = this->get_16_bit_uint_(0x06);
  uint16_t pm_10_0 = this->get_16_bit_uint_(0x08);
  uint16_t pm_1_0_in_air = this->get_16_bit_uint_(0x0A);
  uint16_t pm_2_5_in_air = this->get_16_bit_uint_(0x0C);
  uint16_t pm_10_0_in_air = this->get_16_bit_uint_(0x0E);

  uint16_t pm_particles_0_3um = this->get_16_bit_uint_(0x10);
  uint16_t pm_particles_0_5um = this->get_16_bit_uint_(0x12);
  uint16_t pm_particles_1_0um = this->get_16_bit_uint_(0x14);
  uint16_t pm_particles_2_5um = this->get_16_bit_uint_(0x16);
  uint16_t pm_particles_5_0um = this->get_16_bit_uint_(0x18);
  uint16_t pm_particles_10_0um = this->get_16_bit_uint_(0x1A);

  uint16_t tvoc = this->get_16_bit_uint_(0x1C);
  uint16_t eco2 = this->get_16_bit_uint_(0x1E);
  float temperature = this->get_16_bit_uint_(0x22) * 0.1f;
  float humidity = this->get_16_bit_uint_(0x24) * 0.1f;
  float temperature_raw = this->get_16_bit_uint_(0x26) * 0.1f;
  float humidity_raw = this->get_16_bit_uint_(0x28) * 0.1f;
  
  uint32_t rs0 = this->get_32_bit_uint_(0x2A);
  uint32_t rs1 = this->get_32_bit_uint_(0x2E);
  uint32_t rs2 = this->get_32_bit_uint_(0x32);
  uint32_t rs3 = this->get_32_bit_uint_(0x36);

  // AQI and Error Code
  uint8_t aqi = this->data_[0x3A];
  uint8_t error_code = this->data_[0x3D];

  if (aqi == 0) {
    ESP_LOGW(TAG, "APC1 AQI is 0, skipping invalid or initializing frame.");
    return;
  }

  if (error_code != 0) {
    ESP_LOGW(TAG, "APC1 Sensor Error Code: 0x%02X", error_code);
    if (error_code & 0x01) ESP_LOGW(TAG, " - Too many Fan restarts");
    if (error_code & 0x02) ESP_LOGW(TAG, " - Fan-speed low");
    if (error_code & 0x04) ESP_LOGW(TAG, " - Photodiode error");
    if (error_code & 0x08) ESP_LOGW(TAG, " - Fan stopped");
    if (error_code & 0x10) ESP_LOGW(TAG, " - Laser error");
    if (error_code & 0x20) ESP_LOGW(TAG, " - VOC sensor error");
    if (error_code & 0x40) ESP_LOGW(TAG, " - Temperature/Humidity sensor error");
    this->status_set_warning();
  } else {
    this->status_clear_warning();
  }

  if (this->pm_1_0_sensor_ != nullptr) this->pm_1_0_sensor_->publish_state(pm_1_0);
  if (this->pm_2_5_sensor_ != nullptr) this->pm_2_5_sensor_->publish_state(pm_2_5);
  if (this->pm_10_0_sensor_ != nullptr) this->pm_10_0_sensor_->publish_state(pm_10_0);

  if (this->pm_1_0_in_air_sensor_ != nullptr) this->pm_1_0_in_air_sensor_->publish_state(pm_1_0_in_air);
  if (this->pm_2_5_in_air_sensor_ != nullptr) this->pm_2_5_in_air_sensor_->publish_state(pm_2_5_in_air);
  if (this->pm_10_0_in_air_sensor_ != nullptr) this->pm_10_0_in_air_sensor_->publish_state(pm_10_0_in_air);

  if (this->pm_particles_0_3um_sensor_ != nullptr) this->pm_particles_0_3um_sensor_->publish_state(pm_particles_0_3um);
  if (this->pm_particles_0_5um_sensor_ != nullptr) this->pm_particles_0_5um_sensor_->publish_state(pm_particles_0_5um);
  if (this->pm_particles_1_0um_sensor_ != nullptr) this->pm_particles_1_0um_sensor_->publish_state(pm_particles_1_0um);
  if (this->pm_particles_2_5um_sensor_ != nullptr) this->pm_particles_2_5um_sensor_->publish_state(pm_particles_2_5um);
  if (this->pm_particles_5_0um_sensor_ != nullptr) this->pm_particles_5_0um_sensor_->publish_state(pm_particles_5_0um);
  if (this->pm_particles_10_0um_sensor_ != nullptr) this->pm_particles_10_0um_sensor_->publish_state(pm_particles_10_0um);

  if (this->rs0_sensor_ != nullptr) this->rs0_sensor_->publish_state(rs0);
  if (this->rs1_sensor_ != nullptr) this->rs1_sensor_->publish_state(rs1);
  if (this->rs2_sensor_ != nullptr) this->rs2_sensor_->publish_state(rs2);
  if (this->rs3_sensor_ != nullptr) this->rs3_sensor_->publish_state(rs3);

  if (this->tvoc_sensor_ != nullptr) this->tvoc_sensor_->publish_state(tvoc);
  if (this->eco2_sensor_ != nullptr) this->eco2_sensor_->publish_state(eco2);
  if (this->temperature_sensor_ != nullptr) this->temperature_sensor_->publish_state(temperature);
  if (this->humidity_sensor_ != nullptr) this->humidity_sensor_->publish_state(humidity);
  if (this->temperature_raw_sensor_ != nullptr) this->temperature_raw_sensor_->publish_state(temperature_raw);
  if (this->humidity_raw_sensor_ != nullptr) this->humidity_raw_sensor_->publish_state(humidity_raw);
  if (this->error_code_sensor_ != nullptr) this->error_code_sensor_->publish_state(error_code);
  if (this->aqi_sensor_ != nullptr) this->aqi_sensor_->publish_state(aqi);
}

}  // namespace apc1
}  // namespace esphome
