#include "driver/i2c_master.h"
#include "ssd1306.h"
#include <app_common.h>
#include <dht.h>
#include <string.h>

#define SENSOR_TYPE DHT_TYPE_DHT11
#define DHT_GPIO 27

#define I2C_SDA_GPIO 26
#define I2C_SCL_GPIO 25
#define I2C_FREQ_HZ 400000

static i2c_master_bus_handle_t i2c_bus = nullptr;
static ssd1306_handle_t oled_dev = nullptr;

void i2c_init_for_oled() {
	i2c_master_bus_config_t bus_config = {};
	bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
	bus_config.i2c_port = I2C_NUM_0;
	bus_config.scl_io_num = (gpio_num_t)I2C_SCL_GPIO;
	bus_config.sda_io_num = (gpio_num_t)I2C_SDA_GPIO;
	bus_config.glitch_ignore_cnt = 7;
	bus_config.flags.enable_internal_pullup = true;

	i2c_new_master_bus(&bus_config, &i2c_bus);
}

void oled_init() {
	ssd1306_config_t config = {};
	config.i2c_address = 0x3C;
	config.i2c_clock_speed = 400000;
	config.panel_size = SSD1306_PANEL_128x64;
	config.offset_x = 0;
	config.flip_enabled = false;
	config.display_enabled = true;

	ssd1306_init(i2c_bus, &config, &oled_dev);
	if (oled_dev == nullptr) {
		std::cout << "OLED init failed!" << std::endl;
		return;
	}
	ssd1306_set_contrast(oled_dev, 0xFF);
	ssd1306_clear_display(oled_dev, false);
}

void oled_display_readings(float temperature, float humidity) {
	if (oled_dev == nullptr)
		return;

	// ssd1306_clear_display(oled_dev, false);

	char buf[32];

	snprintf(buf, sizeof(buf), "Temp: %.1f C", temperature);
	ssd1306_display_text(oled_dev, 0, buf, false);

	snprintf(buf, sizeof(buf), "Hum:  %.1f %%", humidity);
	ssd1306_display_text(oled_dev, 2, buf, false);
}

int main() {
	std::cout << "Starting DHT11 + OLED with esp_ssd1306 demo" << std::endl;

	i2c_init_for_oled();
	oled_init();

	float temperature = 0.0f, humidity = 0.0f;

	while (true) {
		if (dht_read_float_data(SENSOR_TYPE, (gpio_num_t)DHT_GPIO, &humidity, &temperature) == ESP_OK) {
			std::cout << "\rHumidity: " << humidity << "% | Temperature: " << temperature << " C   " << std::flush;
			oled_display_readings(temperature, humidity);
		} else {
			std::cout << "\rFailed to read from DHT sensor!            " << std::flush;
			if (oled_dev) {
				ssd1306_clear_display(oled_dev, false);
				ssd1306_display_text(oled_dev, 0, "Sensor error!", false);
			}
		}

		vTaskDelay(pdMS_TO_TICKS(50));
	}

	return 0;
}

APP_MAIN_ENTRY