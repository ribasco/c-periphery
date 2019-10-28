/*
 * c-periphery
 * https://github.com/vsergeev/c-periphery
 * License: MIT
 */

#ifndef _PERIPHERY_GPIO_H
#define _PERIPHERY_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum cp_gpio_error_code {
    GPIO_ERROR_ARG                  = -1,   /* Invalid arguments */
    GPIO_ERROR_OPEN                 = -2,   /* Opening GPIO */
    GPIO_ERROR_NOT_FOUND            = -3,   /* Line name not found */
    GPIO_ERROR_QUERY                = -4,   /* Querying GPIO attributes */
    GPIO_ERROR_CONFIGURE            = -5,   /* Configuring GPIO attributes */
    GPIO_ERROR_UNSUPPORTED          = -6,   /* Unsupported attribute or operation */
    GPIO_ERROR_INVALID_OPERATION    = -7,   /* Invalid operation */
    GPIO_ERROR_IO                   = -8,   /* Reading/writing GPIO */
    GPIO_ERROR_CLOSE                = -9,   /* Closing GPIO */
};

typedef enum cp_gpio_direction {
    GPIO_DIR_IN,        /* Input */
    GPIO_DIR_OUT,       /* Output, initialized to low */
    GPIO_DIR_OUT_LOW,   /* Output, initialized to low */
    GPIO_DIR_OUT_HIGH,  /* Output, initialized to high */
} cp_gpio_direction_t;

typedef enum cp_gpio_edge {
    GPIO_EDGE_NONE,     /* No interrupt edge */
    GPIO_EDGE_RISING,   /* Rising edge 0 -> 1 */
    GPIO_EDGE_FALLING,  /* Falling edge 1 -> 0 */
    GPIO_EDGE_BOTH      /* Both edges X -> !X */
} cp_gpio_edge_t;

typedef struct cp_gpio_handle gpio_t;

/* Primary Functions */
gpio_t *cp_gpio_new(void);
int cp_gpio_open(gpio_t *gpio, const char *path, unsigned int line, cp_gpio_direction_t direction);
int cp_gpio_open_name(gpio_t *gpio, const char *path, const char *name, cp_gpio_direction_t direction);
int cp_gpio_open_sysfs(gpio_t *gpio, unsigned int line, cp_gpio_direction_t direction);
int cp_gpio_read(gpio_t *gpio, bool *value);
int cp_gpio_write(gpio_t *gpio, bool value);
int cp_gpio_poll(gpio_t *gpio, int timeout_ms);
int cp_gpio_close(gpio_t *gpio);
void cp_gpio_free(gpio_t *gpio);

/* Read Event (for character device GPIOs) */
int cp_gpio_read_event(gpio_t *gpio, cp_gpio_edge_t *edge, uint64_t *timestamp);

/* Getters */
int cp_gpio_get_direction(gpio_t *gpio, cp_gpio_direction_t *direction);
int cp_gpio_get_edge(gpio_t *gpio, cp_gpio_edge_t *edge);

/* Setters */
int cp_gpio_set_direction(gpio_t *gpio, cp_gpio_direction_t direction);
int cp_gpio_set_edge(gpio_t *gpio, cp_gpio_edge_t edge);

/* Miscellaneous Properties */
unsigned int cp_gpio_line(gpio_t *gpio);
int cp_gpio_fd(gpio_t *gpio);
int cp_gpio_name(gpio_t *gpio, char *str, size_t len);
int cp_gpio_chip_fd(gpio_t *gpio);
int cp_gpio_chip_name(gpio_t *gpio, char *str, size_t len);
int cp_gpio_chip_label(gpio_t *gpio, char *str, size_t len);
int cp_gpio_tostring(gpio_t *gpio, char *str, size_t len);

/* Error Handling */
int cp_gpio_errno(gpio_t *gpio);
const char *cp_gpio_errmsg(gpio_t *gpio);

#ifdef __cplusplus
}
#endif

#endif

