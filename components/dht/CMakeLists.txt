# Copyright 2024 Zorxx Software. All rights reserved.
idf_component_register(SRCS "dht.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_driver_gpio)
