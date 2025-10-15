set(SOURCES ./main.cpp)

idf_component_register(SRCS ${SOURCES}
                    PRIV_REQUIRES spi_flash dht
                    INCLUDE_DIRS ".")