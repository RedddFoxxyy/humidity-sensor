#include <app_common.h>
#include <dht.h>

#define SENSOR_TYPE DHT_TYPE_DHT11
#define DHT_GPIO 27

int main() {
	std::cout << "DHT11 Sensor Reading Started\n";

	float temperature, humidity;

	while (true) {
		if (dht_read_float_data(SENSOR_TYPE, (gpio_num_t)DHT_GPIO, &humidity, &temperature) == ESP_OK) {
			std::cout << "\rHumidity: " << humidity << "% | Temperature: " << temperature << "°C" << std::flush;
		} else {
			std::cout << "\rFailed to read from DHT sensor!" << std::flush;
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}

	return 0;
}

APP_MAIN_ENTRY