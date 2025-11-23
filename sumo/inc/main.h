#ifndef MAIN_H
#define MAIN_H
/**
 * \file main.h
 * \brief Main header file
 *        Should be used for common definitions
 *        Includes debugging and logging settings
 */

#ifndef LED_PIN
#define LED_PIN CYW43_WL_GPIO_LED_PIN
#endif

// #define DEBUG 1 // Uncomment to enable debug prints
#ifdef DEBUG
#define DEBUG_printf(...) printf(__VA_ARGS__)
#else
#define DEBUG_printf(...) // this is a no-op
#endif

#endif // MAIN_H
