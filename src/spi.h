/*
 * c-periphery
 * https://github.com/vsergeev/c-periphery
 * License: MIT
 */

#ifndef _PERIPHERY_SPI_H
#define _PERIPHERY_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

enum cp_spi_error_code {
    SPI_ERROR_ARG           = -1, /* Invalid arguments */
    SPI_ERROR_OPEN          = -2, /* Opening SPI device */
    SPI_ERROR_QUERY         = -3, /* Querying SPI device attributes */
    SPI_ERROR_CONFIGURE     = -4, /* Configuring SPI device attributes */
    SPI_ERROR_TRANSFER      = -5, /* SPI transfer */
    SPI_ERROR_CLOSE         = -6, /* Closing SPI device */
};

typedef enum cp_spi_bit_order {
    MSB_FIRST,
    LSB_FIRST,
} spi_bit_order_t;

typedef struct cp_spi_handle cp_spi_t;

/* Primary Functions */
cp_spi_t *cp_spi_new(void);
int cp_spi_open(cp_spi_t *spi, const char *path, unsigned int mode,
                uint32_t max_speed);
int cp_spi_open_advanced(cp_spi_t *spi, const char *path, unsigned int mode,
                         uint32_t max_speed, spi_bit_order_t bit_order,
                         uint8_t bits_per_word, uint8_t extra_flags);
int cp_spi_transfer(cp_spi_t *spi, const uint8_t *txbuf, uint8_t *rxbuf, size_t len);
int cp_spi_close(cp_spi_t *spi);
void cp_spi_free(cp_spi_t *spi);

/* Getters */
int cp_spi_get_mode(cp_spi_t *spi, unsigned int *mode);
int cp_spi_get_max_speed(cp_spi_t *spi, uint32_t *max_speed);
int cp_spi_get_bit_order(cp_spi_t *spi, spi_bit_order_t *bit_order);
int cp_spi_get_bits_per_word(cp_spi_t *spi, uint8_t *bits_per_word);
int cp_spi_get_extra_flags(cp_spi_t *spi, uint8_t *extra_flags);

/* Setters */
int cp_spi_set_mode(cp_spi_t *spi, unsigned int mode);
int cp_spi_set_max_speed(cp_spi_t *spi, uint32_t max_speed);
int cp_spi_set_bit_order(cp_spi_t *spi, spi_bit_order_t bit_order);
int cp_spi_set_bits_per_word(cp_spi_t *spi, uint8_t bits_per_word);
int cp_spi_set_extra_flags(cp_spi_t *spi, uint8_t extra_flags);

/* Miscellaneous */
int cp_spi_fd(cp_spi_t *spi);
int cp_spi_tostring(cp_spi_t *spi, char *str, size_t len);

/* Error Handling */
int cp_spi_errno(cp_spi_t *spi);
const char *cp_spi_errmsg(cp_spi_t *spi);

#ifdef __cplusplus
}
#endif

#endif

