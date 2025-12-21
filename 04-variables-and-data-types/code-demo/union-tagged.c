#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  SENSOR_TEMPERATURE,
  SENSOR_HUMIDITY,
  SENSOR_PRESSURE
} SensorType;

typedef struct {
  SensorType type;
  union {
    float temperature;
    float humidity;
    uint32_t pressure;
  } data;
} SensorReading;

void print_sensor_reading(const SensorReading *reading) {
  switch (reading->type) {
  case SENSOR_TEMPERATURE:
    printf("Temperature: %.2f °C\n", reading->data.temperature);
    break;
  case SENSOR_HUMIDITY:
    printf("Humidity: %.2f %%\n", reading->data.humidity);
    break;
  case SENSOR_PRESSURE:
    printf("Pressure: %u Pa\n", reading->data.pressure);
    break;
  default:
    printf("Unknown sensor type\n");
    break;
  }
}

int main(void) {
  printf("=== Tagged Union Demo ===\n\n");

  SensorReading readings[3];

  readings[0].type = SENSOR_TEMPERATURE;
  readings[0].data.temperature = 25.5f;

  readings[1].type = SENSOR_HUMIDITY;
  readings[1].data.humidity = 65.0f;

  readings[2].type = SENSOR_PRESSURE;
  readings[2].data.pressure = 101325U;

  for (int i = 0; i < 3; i++) {
    printf("Sensor %d: ", i + 1);
    print_sensor_reading(&readings[i]);
  }

  printf("\nMemory usage:\n");
  printf("  sizeof(SensorReading) = %zu bytes\n", sizeof(SensorReading));
  printf("  Total for 3 sensors = %zu bytes\n", 3 * sizeof(SensorReading));

  return 0;
}