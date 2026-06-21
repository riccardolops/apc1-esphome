import esphome.codegen as cg
from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_PM_1_0,
    CONF_PM_2_5,
    CONF_PM_10_0,
    CONF_TEMPERATURE,
    CONF_HUMIDITY,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_PM1,
    DEVICE_CLASS_PM10,
    DEVICE_CLASS_PM25,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLATILE_ORGANIC_COMPOUNDS,
    DEVICE_CLASS_CARBON_DIOXIDE,
    DEVICE_CLASS_AQI,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_MICROGRAMS_PER_CUBIC_METER,
    UNIT_PERCENT,
    UNIT_PARTS_PER_BILLION,
    UNIT_PARTS_PER_MILLION,
)

# Optional icons for clarity
ICON_CHEMICAL_WEAPON = "mdi:chemical-weapon"
ICON_MOLECULE_CO2 = "mdi:molecule-co2"
ICON_FLASK = "mdi:flask"
ICON_THERMOMETER = "mdi:thermometer"
ICON_WATER_PERCENT = "mdi:water-percent"

DEPENDENCIES = ["uart"]

CONF_PM_1_0_IN_AIR = "pm_1_0_in_air"
CONF_PM_2_5_IN_AIR = "pm_2_5_in_air"
CONF_PM_10_0_IN_AIR = "pm_10_0_in_air"

CONF_PM_0_3UM = "pm_0_3um"
CONF_PM_0_5UM = "pm_0_5um"
CONF_PM_1_0UM = "pm_1_0um"
CONF_PM_2_5UM = "pm_2_5um"
CONF_PM_5_0UM = "pm_5_0um"
CONF_PM_10_0UM = "pm_10_0um"

CONF_RS0 = "rs0"
CONF_RS1 = "rs1"
CONF_RS2 = "rs2"
CONF_RS3 = "rs3"
CONF_AQI = "aqi"
CONF_TVOC = "tvoc"
CONF_ECO2 = "eco2"
CONF_TEMPERATURE_RAW = "temperature_raw"
CONF_HUMIDITY_RAW = "humidity_raw"
CONF_ERROR_CODE = "error_code"

UNIT_COUNT_DECILITRE = "#/0.1L"
UNIT_OHMS = "Ω"

apc1_ns = cg.esphome_ns.namespace("apc1")
APC1Component = apc1_ns.class_("APC1Component", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(APC1Component),
            cv.Optional(CONF_PM_1_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM10,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_1_0_IN_AIR): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5_IN_AIR): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0_IN_AIR): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM10,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_0_3UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_0_5UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_1_0UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_5_0UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0UM): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNT_DECILITRE,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_RS0): sensor.sensor_schema(
                unit_of_measurement=UNIT_OHMS,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_RS1): sensor.sensor_schema(
                unit_of_measurement=UNIT_OHMS,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_RS2): sensor.sensor_schema(
                unit_of_measurement=UNIT_OHMS,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_RS3): sensor.sensor_schema(
                unit_of_measurement=UNIT_OHMS,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_TVOC): sensor.sensor_schema(
                unit_of_measurement=UNIT_PARTS_PER_BILLION,
                icon=ICON_FLASK,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_VOLATILE_ORGANIC_COMPOUNDS,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_ECO2): sensor.sensor_schema(
                unit_of_measurement=UNIT_PARTS_PER_MILLION,
                icon=ICON_MOLECULE_CO2,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_CARBON_DIOXIDE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon=ICON_WATER_PERCENT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_HUMIDITY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_AQI): sensor.sensor_schema(
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_AQI,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_TEMPERATURE_RAW): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_HUMIDITY_RAW): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon=ICON_WATER_PERCENT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_HUMIDITY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_ERROR_CODE): sensor.sensor_schema(
                icon="mdi:alert-circle",
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA),
)

def final_validate(config):
    schema = uart.final_validate_device_schema(
        "apc", baud_rate=9600, require_rx=True, require_tx=True
    )
    schema(config)

FINAL_VALIDATE_SCHEMA = final_validate

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PM_1_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0])
        cg.add(var.set_pm_1_0_sensor(sens))
    if CONF_PM_2_5 in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5])
        cg.add(var.set_pm_2_5_sensor(sens))
    if CONF_PM_10_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0])
        cg.add(var.set_pm_10_0_sensor(sens))

    if CONF_PM_1_0_IN_AIR in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0_IN_AIR])
        cg.add(var.set_pm_1_0_in_air_sensor(sens))
    if CONF_PM_2_5_IN_AIR in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5_IN_AIR])
        cg.add(var.set_pm_2_5_in_air_sensor(sens))
    if CONF_PM_10_0_IN_AIR in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0_IN_AIR])
        cg.add(var.set_pm_10_0_in_air_sensor(sens))

    if CONF_PM_0_3UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_3UM])
        cg.add(var.set_pm_particles_0_3um_sensor(sens))
    if CONF_PM_0_5UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_5UM])
        cg.add(var.set_pm_particles_0_5um_sensor(sens))
    if CONF_PM_1_0UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0UM])
        cg.add(var.set_pm_particles_1_0um_sensor(sens))
    if CONF_PM_2_5UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5UM])
        cg.add(var.set_pm_particles_2_5um_sensor(sens))
    if CONF_PM_5_0UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_5_0UM])
        cg.add(var.set_pm_particles_5_0um_sensor(sens))
    if CONF_PM_10_0UM in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0UM])
        cg.add(var.set_pm_particles_10_0um_sensor(sens))

    if CONF_RS0 in config:
        sens = await sensor.new_sensor(config[CONF_RS0])
        cg.add(var.set_rs0_sensor(sens))
    if CONF_RS1 in config:
        sens = await sensor.new_sensor(config[CONF_RS1])
        cg.add(var.set_rs1_sensor(sens))
    if CONF_RS2 in config:
        sens = await sensor.new_sensor(config[CONF_RS2])
        cg.add(var.set_rs2_sensor(sens))
    if CONF_RS3 in config:
        sens = await sensor.new_sensor(config[CONF_RS3])
        cg.add(var.set_rs3_sensor(sens))

    if CONF_TVOC in config:
        sens = await sensor.new_sensor(config[CONF_TVOC])
        cg.add(var.set_tvoc_sensor(sens))
    if CONF_ECO2 in config:
        sens = await sensor.new_sensor(config[CONF_ECO2])
        cg.add(var.set_eco2_sensor(sens))
    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))
    if CONF_HUMIDITY in config:
        sens = await sensor.new_sensor(config[CONF_HUMIDITY])
        cg.add(var.set_humidity_sensor(sens))
    if CONF_TEMPERATURE_RAW in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_RAW])
        cg.add(var.set_temperature_raw_sensor(sens))
    if CONF_HUMIDITY_RAW in config:
        sens = await sensor.new_sensor(config[CONF_HUMIDITY_RAW])
        cg.add(var.set_humidity_raw_sensor(sens))
    if CONF_ERROR_CODE in config:
        sens = await sensor.new_sensor(config[CONF_ERROR_CODE])
        cg.add(var.set_error_code_sensor(sens))
    if CONF_AQI in config:
        sens = await sensor.new_sensor(config[CONF_AQI])
        cg.add(var.set_aqi_sensor(sens))
