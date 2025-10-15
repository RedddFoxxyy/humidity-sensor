set(SOURCES ./main.cpp)

idf_component_register(
	SRCS ${SOURCES}
	PRIV_REQUIRES 
		spi_flash 
		dht 
		esp_ssd1306 
		esp_driver_gpio
	INCLUDE_DIRS "."
)