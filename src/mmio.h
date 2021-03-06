/*
 * c-periphery
 * https://github.com/vsergeev/c-periphery
 * License: MIT
 */

#ifndef _PERIPHERY_MMIO_H
#define _PERIPHERY_MMIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

enum cp_mmio_error_code {
    MMIO_ERROR_ARG          = -1, /* Invalid arguments */
    MMIO_ERROR_OPEN         = -2, /* Opening MMIO */
    MMIO_ERROR_CLOSE        = -3, /* Closing MMIO */
};

typedef struct mmio_handle mmio_t;

/* Primary Functions */
mmio_t *cp_mmio_new(void);
int cp_mmio_open(mmio_t *mmio, uintptr_t base, size_t size);
void *cp_mmio_ptr(mmio_t *mmio);
int cp_mmio_read32(mmio_t *mmio, uintptr_t offset, uint32_t *value);
int cp_mmio_read16(mmio_t *mmio, uintptr_t offset, uint16_t *value);
int cp_mmio_read8(mmio_t *mmio, uintptr_t offset, uint8_t *value);
int cp_mmio_read(mmio_t *mmio, uintptr_t offset, uint8_t *buf, size_t len);
int cp_mmio_write32(mmio_t *mmio, uintptr_t offset, uint32_t value);
int cp_mmio_write16(mmio_t *mmio, uintptr_t offset, uint16_t value);
int cp_mmio_write8(mmio_t *mmio, uintptr_t offset, uint8_t value);
int cp_mmio_write(mmio_t *mmio, uintptr_t offset, const uint8_t *buf, size_t len);
int cp_mmio_close(mmio_t *mmio);
void cp_mmio_free(mmio_t *mmio);

/* Miscellaneous */
uintptr_t cp_mmio_base(mmio_t *mmio);
size_t cp_mmio_size(mmio_t *mmio);
int cp_mmio_tostring(mmio_t *mmio, char *str, size_t len);

/* Error Handling */
int cp_mmio_errno(mmio_t *mmio);
const char *cp_mmio_errmsg(mmio_t *mmio);

#ifdef __cplusplus
}
#endif

#endif

