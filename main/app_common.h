#pragma once

/*
    Base Imports
*/
#include "esp_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#ifdef __cplusplus

#include <cstdint>
#include <iostream>

#else

#include <stdint.h>
#include <stdio.h>

#endif

/*
    Defines a macro to be called after the main function when writing C++ code.

    This macro expands to the app_main function when used in a C file and to
    unmangled function when used in C++
*/
#ifdef __cplusplus
#define APP_MAIN_ENTRY                                                                                                 \
	extern "C" void app_main(void) { main(); }
#else
#define APP_MAIN_ENTRY                                                                                                 \
	void app_main(void) { main(); }
#endif