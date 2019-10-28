/*
 * c-periphery
 * https://github.com/vsergeev/c-periphery
 * License: MIT
 */

#ifndef _PERIPHERY_SERIAL_H
#define _PERIPHERY_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

enum cp_serial_error_code {
    SERIAL_ERROR_ARG            = -1, /* Invalid arguments */
    SERIAL_ERROR_OPEN           = -2, /* Opening serial port */
    SERIAL_ERROR_QUERY          = -3, /* Querying serial port attributes */
    SERIAL_ERROR_CONFIGURE      = -4, /* Configuring serial port attributes */
    SERIAL_ERROR_IO             = -5, /* Reading/writing serial port */
    SERIAL_ERROR_CLOSE          = -6, /* Closing serial port */
};

typedef enum cp_serial_parity {
    PARITY_NONE,
    PARITY_ODD,
    PARITY_EVEN,
} cp_serial_parity_t;

typedef struct cp_serial_handle cp_serial_t;

/* Primary Functions */
cp_serial_t *cp_serial_new(void);
int cp_serial_open(cp_serial_t *serial, const char *path, uint32_t baudrate);
int cp_serial_open_advanced(cp_serial_t *serial, const char *path,
                            uint32_t baudrate, unsigned int databits,
                            cp_serial_parity_t parity, unsigned int stopbits,
                            bool xonxoff, bool rtscts);
int cp_serial_read(cp_serial_t *serial, uint8_t *buf, size_t len, int timeout_ms);
int cp_serial_write(cp_serial_t *serial, const uint8_t *buf, size_t len);
int cp_serial_flush(cp_serial_t *serial);
int cp_serial_input_waiting(cp_serial_t *serial, unsigned int *count);
int cp_serial_output_waiting(cp_serial_t *serial, unsigned int *count);
int cp_serial_poll(cp_serial_t *serial, int timeout_ms);
int cp_serial_close(cp_serial_t *serial);
void cp_serial_free(cp_serial_t *serial);

/* Getters */
int cp_serial_get_baudrate(cp_serial_t *serial, uint32_t *baudrate);
int cp_serial_get_databits(cp_serial_t *serial, unsigned int *databits);
int cp_serial_get_parity(cp_serial_t *serial, cp_serial_parity_t *parity);
int cp_serial_get_stopbits(cp_serial_t *serial, unsigned int *stopbits);
int cp_serial_get_xonxoff(cp_serial_t *serial, bool *xonxoff);
int cp_serial_get_rtscts(cp_serial_t *serial, bool *rtscts);

/* Setters */
int cp_serial_set_baudrate(cp_serial_t *serial, uint32_t baudrate);
int cp_serial_set_databits(cp_serial_t *serial, unsigned int databits);
int cp_serial_set_parity(cp_serial_t *serial, enum cp_serial_parity parity);
int cp_serial_set_stopbits(cp_serial_t *serial, unsigned int stopbits);
int cp_serial_set_xonxoff(cp_serial_t *serial, bool enabled);
int cp_serial_set_rtscts(cp_serial_t *serial, bool enabled);

/* Miscellaneous */
int cp_serial_fd(cp_serial_t *serial);
int cp_serial_tostring(cp_serial_t *serial, char *str, size_t len);

/* Error Handling */
int cp_serial_errno(cp_serial_t *serial);
const char *cp_serial_errmsg(cp_serial_t *serial);

#ifdef __cplusplus
}
#endif

#endif

