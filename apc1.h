#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace apc1 {

class APC1Component : public PollingComponent, public uart::UARTDevice {
 public:
  APC1Component() = default;
  void setup() override;
  void loop() override;
  void update() override;
  void dump_config() override;
  
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_pm_1_0_sensor(sensor::Sensor *pm_1_0_sensor) { pm_1_0_sensor_ = pm_1_0_sensor; }
  void set_pm_2_5_sensor(sensor::Sensor *pm_2_5_sensor) { pm_2_5_sensor_ = pm_2_5_sensor; }
  void set_pm_10_0_sensor(sensor::Sensor *pm_10_0_sensor) { pm_10_0_sensor_ = pm_10_0_sensor; }
  
  void set_pm_1_0_in_air_sensor(sensor::Sensor *pm_1_0_in_air_sensor) { pm_1_0_in_air_sensor_ = pm_1_0_in_air_sensor; }
  void set_pm_2_5_in_air_sensor(sensor::Sensor *pm_2_5_in_air_sensor) { pm_2_5_in_air_sensor_ = pm_2_5_in_air_sensor; }
  void set_pm_10_0_in_air_sensor(sensor::Sensor *pm_10_0_in_air_sensor) { pm_10_0_in_air_sensor_ = pm_10_0_in_air_sensor; }

  void set_pm_particles_0_3um_sensor(sensor::Sensor *pm_particles_0_3um_sensor) { pm_particles_0_3um_sensor_ = pm_particles_0_3um_sensor; }
  void set_pm_particles_0_5um_sensor(sensor::Sensor *pm_particles_0_5um_sensor) { pm_particles_0_5um_sensor_ = pm_particles_0_5um_sensor; }
  void set_pm_particles_1_0um_sensor(sensor::Sensor *pm_particles_1_0um_sensor) { pm_particles_1_0um_sensor_ = pm_particles_1_0um_sensor; }
  void set_pm_particles_2_5um_sensor(sensor::Sensor *pm_particles_2_5um_sensor) { pm_particles_2_5um_sensor_ = pm_particles_2_5um_sensor; }
  void set_pm_particles_5_0um_sensor(sensor::Sensor *pm_particles_5_0um_sensor) { pm_particles_5_0um_sensor_ = pm_particles_5_0um_sensor; }
  void set_pm_particles_10_0um_sensor(sensor::Sensor *pm_particles_10_0um_sensor) { pm_particles_10_0um_sensor_ = pm_particles_10_0um_sensor; }

  void set_rs0_sensor(sensor::Sensor *rs0_sensor) { rs0_sensor_ = rs0_sensor; }
  void set_rs1_sensor(sensor::Sensor *rs1_sensor) { rs1_sensor_ = rs1_sensor; }
  void set_rs2_sensor(sensor::Sensor *rs2_sensor) { rs2_sensor_ = rs2_sensor; }
  void set_rs3_sensor(sensor::Sensor *rs3_sensor) { rs3_sensor_ = rs3_sensor; }

  void set_tvoc_sensor(sensor::Sensor *tvoc_sensor) { tvoc_sensor_ = tvoc_sensor; }
  void set_eco2_sensor(sensor::Sensor *eco2_sensor) { eco2_sensor_ = eco2_sensor; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
  void set_humidity_sensor(sensor::Sensor *humidity_sensor) { humidity_sensor_ = humidity_sensor; }
  void set_temperature_raw_sensor(sensor::Sensor *temperature_raw_sensor) { temperature_raw_sensor_ = temperature_raw_sensor; }
  void set_humidity_raw_sensor(sensor::Sensor *humidity_raw_sensor) { humidity_raw_sensor_ = humidity_raw_sensor; }
  void set_error_code_sensor(sensor::Sensor *error_code_sensor) { error_code_sensor_ = error_code_sensor; }
  void set_aqi_sensor(sensor::Sensor *aqi_sensor) { aqi_sensor_ = aqi_sensor; }

 protected:
  optional<bool> check_byte_();
  void parse_data_();
  uint16_t get_16_bit_uint_(uint8_t start_index) const;
  uint32_t get_32_bit_uint_(uint8_t start_index) const;

  uint8_t data_[64];
  uint8_t data_index_{0};
  uint32_t last_transmission_{0};

  sensor::Sensor *pm_1_0_sensor_{nullptr};
  sensor::Sensor *pm_2_5_sensor_{nullptr};
  sensor::Sensor *pm_10_0_sensor_{nullptr};
  sensor::Sensor *pm_1_0_in_air_sensor_{nullptr};
  sensor::Sensor *pm_2_5_in_air_sensor_{nullptr};
  sensor::Sensor *pm_10_0_in_air_sensor_{nullptr};
  sensor::Sensor *pm_particles_0_3um_sensor_{nullptr};
  sensor::Sensor *pm_particles_0_5um_sensor_{nullptr};
  sensor::Sensor *pm_particles_1_0um_sensor_{nullptr};
  sensor::Sensor *pm_particles_2_5um_sensor_{nullptr};
  sensor::Sensor *pm_particles_5_0um_sensor_{nullptr};
  sensor::Sensor *pm_particles_10_0um_sensor_{nullptr};
  sensor::Sensor *rs0_sensor_{nullptr};
  sensor::Sensor *rs1_sensor_{nullptr};
  sensor::Sensor *rs2_sensor_{nullptr};
  sensor::Sensor *rs3_sensor_{nullptr};

  sensor::Sensor *tvoc_sensor_{nullptr};
  sensor::Sensor *eco2_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};
  sensor::Sensor *temperature_raw_sensor_{nullptr};
  sensor::Sensor *humidity_raw_sensor_{nullptr};
  sensor::Sensor *error_code_sensor_{nullptr};
  sensor::Sensor *aqi_sensor_{nullptr};
};

}  // namespace apc1
}  // namespace esphome
