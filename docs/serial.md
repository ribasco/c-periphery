### NAME

Serial wrapper functions for Linux userspace termios `tty` devices.

### SYNOPSIS

``` c
#include <periphery/serial.h>

/* Primary Functions */
cp_serial_t *serial_new(void);
int serial_open(cp_serial_t *serial, const char *path, uint32_t baudrate);
int serial_open_advanced(cp_serial_t *serial, const char *path,
                            uint32_t baudrate, unsigned int databits,
                            cp_serial_parity_t parity, unsigned int stopbits,
                            bool xonxoff, bool rtscts);
int serial_read(cp_serial_t *serial, uint8_t *buf, size_t len, int timeout_ms);
int serial_write(cp_serial_t *serial, const uint8_t *buf, size_t len);
int serial_flush(cp_serial_t *serial);
int serial_input_waiting(cp_serial_t *serial, unsigned int *count);
int serial_output_waiting(cp_serial_t *serial, unsigned int *count);
int serial_poll(cp_serial_t *serial, int timeout_ms);
int serial_close(cp_serial_t *serial);
void serial_free(cp_serial_t *serial);

/* Getters */
int serial_get_baudrate(cp_serial_t *serial, uint32_t *baudrate);
int serial_get_databits(cp_serial_t *serial, unsigned int *databits);
int serial_get_parity(cp_serial_t *serial, cp_serial_parity_t *parity);
int serial_get_stopbits(cp_serial_t *serial, unsigned int *stopbits);
int serial_get_xonxoff(cp_serial_t *serial, bool *xonxoff);
int serial_get_rtscts(cp_serial_t *serial, bool *rtscts);

/* Setters */
int serial_set_baudrate(cp_serial_t *serial, uint32_t baudrate);
int serial_set_databits(cp_serial_t *serial, unsigned int databits);
int serial_set_parity(cp_serial_t *serial, enum cp_serial_parity parity);
int serial_set_stopbits(cp_serial_t *serial, unsigned int stopbits);
int serial_set_xonxoff(cp_serial_t *serial, bool enabled);
int serial_set_rtscts(cp_serial_t *serial, bool enabled);

/* Miscellaneous */
int serial_fd(cp_serial_t *serial);
int serial_tostring(cp_serial_t *serial, char *str, size_t len);

/* Error Handling */
int serial_errno(cp_serial_t *serial);
const char *serial_errmsg(cp_serial_t *serial);
```

### ENUMERATIONS

* `cp_serial_parity_t`
    * `PARITY_NONE`: No parity
    * `PARITY_ODD`: Odd parity
    * `PARITY_EVEN`: Even parity

### DESCRIPTION

``` c
cp_serial_t *serial_new(void);
```
Allocate a Serial handle.

Returns a valid handle on success, or NULL on failure.

------

``` c
int serial_open(cp_serial_t *serial, const char *path, uint32_t baudrate);
```
Open the `tty` device at the specified path (e.g. "/dev/ttyUSB0"), with the specified baudrate, and the defaults of 8 data bits, no parity, 1 stop bit, software flow control (xonxoff) off, hardware flow control (rtscts) off.

`serial` should be a valid pointer to an allocated Serial handle structure.

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int serial_open_advanced(cp_serial_t *serial, const char *path,
                            uint32_t baudrate, unsigned int databits,
                            cp_serial_parity_t parity, unsigned int stopbits,
                            bool xonxoff, bool rtscts);
```
Open the `tty` device at the specified path (e.g. "/dev/ttyUSB0"), with the specified baudrate, data bits, parity, stop bits, software flow control (xonxoff), and hardware flow control (rtscts) settings.

`serial` should be a valid pointer to an allocated Serial handle structure. `databits` can be 5, 6, 7, or 8. `parity` can be `PARITY_NONE`, `PARITY_ODD`, or `PARITY_EVEN` as defined [above](#enumerations). `stopbits` can be 1 or 2.

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int serial_read(cp_serial_t *serial, uint8_t *buf, size_t len, int timeout_ms);
```
Read up to `len` number of bytes from the serial port into the `buf` buffer with the specified millisecond timeout. A 0 timeout can be specified for a non-blocking read. A negative timeout can be specified for a blocking read that will read until all of the requested number of bytes are read. A positive timeout in milliseconds can be specified for a blocking read with timeout.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. `timeout_ms` can be positive for a timeout in milliseconds, 0 for a non-blocking read, or a negative number for a blocking read.

Returns the number of bytes read on success, 0 on timeout, or a negative [Serial error code](#return-value) on failure.

------

``` c
int serial_write(cp_serial_t *serial, const uint8_t *buf, size_t len);
```
Write `len` number of bytes from the `buf` buffer to the serial port.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns the number of bytes written on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int cp_serial_flush(cp_serial_t *serial);
```
Flush the write buffer of the serial port (i.e. force its write immediately).

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int cp_serial_input_waiting(cp_serial_t *serial, unsigned int *count);
```
Query the number of bytes waiting to be read from the serial port.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int cp_serial_output_waiting(cp_serial_t *serial, unsigned int *count);
```
Query the number of bytes waiting to be written to the serial port.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
bool cp_serial_poll(cp_serial_t *serial, int timeout_ms);
```
Poll for data available for reading from the serial port.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. `timeout_ms` can be positive for a timeout in milliseconds, 0 for a non-blocking poll, or a negative number for a blocking poll.

Returns 1 on success (data available for reading), 0 on timeout, or a negative [Serial error code](#return-value) on failure.

------

``` c
int serial_close(cp_serial_t *serial);
```
Close the `tty` device.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
void serial_free(cp_serial_t *serial);
```
Free a Serial handle.

------

``` c
int cp_serial_get_baudrate(cp_serial_t *serial, uint32_t *baudrate);
int cp_serial_get_databits(cp_serial_t *serial, unsigned int *databits);
int cp_serial_get_parity(cp_serial_t *serial, cp_serial_parity_t *parity);
int cp_serial_get_stopbits(cp_serial_t *serial, unsigned int *stopbits);
int cp_serial_get_xonxoff(cp_serial_t *serial, bool *xonxoff);
int cp_serial_get_rtscts(cp_serial_t *serial, bool *rtscts);
```
Query the baudrate, data bits, parity, stop bits, software flow control (xonxoff), or hardware flow control (rtscts), respectively, of the underlying `tty` device.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `cp_serial_open_advanced()`.

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int cp_serial_set_baudrate(cp_serial_t *serial, uint32_t baudrate);
int cp_serial_set_databits(cp_serial_t *serial, unsigned int databits);
int cp_serial_set_parity(cp_serial_t *serial, enum cp_serial_parity parity);
int cp_serial_set_stopbits(cp_serial_t *serial, unsigned int stopbits);
int cp_serial_set_xonxoff(cp_serial_t *serial, bool enabled);
int cp_serial_set_rtscts(cp_serial_t *serial, bool enabled);
```
Set the baudrate, data bits, parity, stop bits, software flow control (xonxoff), or hardware flow control (rtscts), respectively, on the underlying `tty` device.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

Returns 0 on success, or a negative [Serial error code](#return-value) on failure.

------

``` c
int cp_serial_fd(cp_serial_t *serial);
```
Return the file descriptor (for the underlying `tty` device) of the Serial handle.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

This function is a simple accessor to the Serial handle structure and always succeeds.

------

``` c
int cp_serial_tostring(cp_serial_t *serial, char *str, size_t len);
```
Return a string representation of the Serial handle.

`serial` should be a valid pointer to a Serial handle opened with `cp_serial_open()` or `serial_open_advanced()`.

This function behaves and returns like `snprintf()`.

------

``` c
int serial_errno(cp_serial_t *serial);
```
Return the libc errno of the last failure that occurred.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

------

``` c
const char *serial_errmsg(cp_serial_t *serial);
```
Return a human readable error message of the last failure that occurred.

`serial` should be a valid pointer to a Serial handle opened with `serial_open()` or `serial_open_advanced()`. 

### RETURN VALUE

The periphery Serial functions return 0 on success or one of the negative error codes below on failure.

The libc errno of the failure in an underlying libc library call can be obtained with the `cp_serial_errno()` helper function. A human readable error message can be obtained with the `serial_errmsg()` helper function.

| Error Code                | Description                           |
|---------------------------|---------------------------------------|
| `SERIAL_ERROR_ARG`        | Invalid arguments                     |
| `SERIAL_ERROR_OPEN`       | Opening serial port                   |
| `SERIAL_ERROR_QUERY`      | Querying serial port attributes       |
| `SERIAL_ERROR_CONFIGURE`  | Configuring serial port attributes    |
| `SERIAL_ERROR_IO`         | Reading/writing serial port           |
| `SERIAL_ERROR_CLOSE`      | Closing serial port                   |

### EXAMPLE

``` c
#include <stdio.h>
#include <stdlib.h>

#include "serial.h"

int main(void) {
    cp_serial_t *serial;
    const char *s = "Hello World!";
    char buf[128];
    int ret;

    serial = cp_serial_new();

    /* Open /dev/ttyUSB0 with baudrate 115200, and defaults of 8N1, no flow control */
    if (serial_open(serial, "/dev/ttyUSB0", 115200) < 0) {
        fprintf(stderr, "serial_open(): %s\n", serial_errmsg(serial));
        exit(1);
    }

    /* Write to the serial port */
    if (serial_write(serial, s, strlen(s)) < 0) {
        fprintf(stderr, "cp_serial_write(): %s\n", serial_errmsg(serial));
        exit(1);
    }

    /* Read up to buf size or 2000ms timeout */
    if ((ret = serial_read(serial, buf, sizeof(buf), 2000)) < 0) {
        fprintf(stderr, "cp_serial_read(): %s\n", cp_serial_errmsg(serial));
        exit(1);
    }

    printf("read %d bytes: _%s_\n", ret, buf);

    cp_serial_close(serial);

    cp_serial_free(serial);

    return 0;
}
```

