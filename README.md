# ESPHome APC1 Component

This is a custom `external_components` integration for **ESPHome** to support the [ScioSense APC1 Air Quality Combo Sensor](https://www.sciosense.com/apc1-air-quality-combo-sensor/).

The APC1 is a comprehensive, all-in-one environmental sensor that measures Particulate Matter (PM1.0, PM2.5, PM10), Volatile Organic Compounds (TVOC), estimated CO2 (eCO2), Air Quality Index (AQI), Temperature, and Humidity.

This component seamlessly integrates the 64-byte UART payload of the sensor into the ESPHome ecosystem, exposing all 20 available parameters without blocking the main loop.

## Features
- **Particulate Matter (Standard & Environmental)**: PM1.0, PM2.5, PM10
- **Particle Count (per 0.1L)**: >0.3µm, >0.5µm, >1.0µm, >2.5µm, >5.0µm, >10.0µm
- **Gas Sensors**: TVOC, eCO2, and Raw resistance values (RS0, RS1, RS2, RS3)
- **Environmental**: Compensated and Uncompensated (Raw) Temperature and Humidity
- **Status**: Air Quality Index (AQI) (UBA scale 1-5) and specific Error Codes.

## Installation & Configuration

You can easily use this component in your ESPHome node without needing to manually copy files. Just use the `external_components` integration and point to this GitHub repository.

Here is a full example `yaml` configuration:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/riccardolops/apc1-esphome
    components: [ apc ]

uart:
  rx_pin: GPIO3 # Connect to APC1 TX
  tx_pin: GPIO1 # Connect to APC1 RX
  baud_rate: 9600

sensor:
  - platform: apc
    update_interval: 60s
    # Mass Concentration (Standard)
    pm_1_0:
      name: "APC1 PM1.0"
    pm_2_5:
      name: "APC1 PM2.5"
    pm_10_0:
      name: "APC1 PM10.0"
    # Mass Concentration (Atmospheric Environment)
    pm_1_0_in_air:
      name: "APC1 PM1.0 In Air"
    pm_2_5_in_air:
      name: "APC1 PM2.5 In Air"
    pm_10_0_in_air:
      name: "APC1 PM10.0 In Air"
    # Particle Count (per 0.1L)
    pm_0_3um:
      name: "APC1 Particles > 0.3um"
    pm_0_5um:
      name: "APC1 Particles > 0.5um"
    pm_1_0um:
      name: "APC1 Particles > 1.0um"
    pm_2_5um:
      name: "APC1 Particles > 2.5um"
    pm_5_0um:
      name: "APC1 Particles > 5.0um"
    pm_10_0um:
      name: "APC1 Particles > 10.0um"
    # Gases
    tvoc:
      name: "APC1 TVOC"
    eco2:
      name: "APC1 eCO2"
    rs0:
      name: "APC1 RS0 Raw"
    rs1:
      name: "APC1 RS1 Raw"
    rs2:
      name: "APC1 RS2 Raw"
    rs3:
      name: "APC1 RS3 Raw"
    # Temperature & Humidity
    temperature:
      name: "APC1 Temperature"
    humidity:
      name: "APC1 Humidity"
    temperature_raw:
      name: "APC1 Raw Temperature"
    humidity_raw:
      name: "APC1 Raw Humidity"
    # Status
    aqi:
      name: "APC1 AQI"
    error_code:
      name: "APC1 Error Code"
```

## Error Codes
The `error_code` sensor exposes internal bit-flags. You can monitor the ESPHome logs for textual descriptions:
- `0x01`: Too many Fan restarts
- `0x02`: Fan-speed low
- `0x04`: Photodiode error
- `0x08`: Fan stopped
- `0x10`: Laser error
- `0x20`: VOC sensor error
- `0x40`: Temperature/Humidity sensor error
