### NAME

GPIO wrapper functions for Linux userspace character device `gpio-cdev` and sysfs GPIOs.

### SYNOPSIS

``` c
#include <periphery/gpio.h>

/* Primary Functions */
gpio_t *gpio_new(void);
int gpio_open(gpio_t *gpio, const char *path, unsigned int line, cp_gpio_direction_t direction);
int gpio_open_name(gpio_t *gpio, const char *path, const char *name, cp_gpio_direction_t direction);
int gpio_open_sysfs(gpio_t *gpio, unsigned int line, cp_gpio_direction_t direction);
int gpio_read(gpio_t *gpio, bool *value);
int gpio_write(gpio_t *gpio, bool value);
int gpio_poll(gpio_t *gpio, int timeout_ms);
int gpio_close(gpio_t *gpio);
void gpio_free(gpio_t *gpio);

/* Read Event (for character device GPIOs) */
int gpio_read_event(gpio_t *gpio, cp_gpio_edge_t *edge, uint64_t *timestamp);

/* Getters */
int gpio_get_direction(gpio_t *gpio, cp_gpio_direction_t *direction);
int gpio_get_edge(gpio_t *gpio, cp_gpio_edge_t *edge);

/* Setters */
int gpio_set_direction(gpio_t *gpio, cp_gpio_direction_t direction);
int gpio_set_edge(gpio_t *gpio, cp_gpio_edge_t edge);

/* Miscellaneous Properties */
unsigned int gpio_line(gpio_t *gpio);
int gpio_fd(gpio_t *gpio);
int gpio_name(gpio_t *gpio, char *str, size_t len);
int gpio_chip_fd(gpio_t *gpio);
int gpio_chip_name(gpio_t *gpio, char *str, size_t len);
int gpio_chip_label(gpio_t *gpio, char *str, size_t len);
int gpio_tostring(gpio_t *gpio, char *str, size_t len);

/* Error Handling */
int gpio_errno(gpio_t *gpio);
const char *gpio_errmsg(gpio_t *gpio);
```

### ENUMERATIONS

* `cp_gpio_direction_t`
    * `GPIO_DIR_IN`: Input
    * `GPIO_DIR_OUT`: Output, initialized to low
    * `GPIO_DIR_OUT_LOW`: Output, initialized to low
    * `GPIO_DIR_OUT_HIGH`: Output, initialized to high

* `cp_gpio_edge_t`
    * `GPIO_EDGE_NONE`: No interrupt edge
    * `GPIO_EDGE_RISING`: Rising edge (0 -> 1 transition)
    * `GPIO_EDGE_FALLING`: Falling edge (1 -> 0 transition)
    * `GPIO_EDGE_BOTH`: Both edges (X -> !X transition)

### DESCRIPTION

``` c
gpio_t *gpio_new(void);
```
Allocate a GPIO handle.

Returns a valid handle on success, or NULL on failure.

------

``` c
int gpio_open(gpio_t *gpio, const char *path, unsigned int line, cp_gpio_direction_t direction);
```
Open the character device GPIO with the specified GPIO line and direction at the specified character device GPIO chip path (e.g. `/dev/gpiochip0`).

`gpio` should be a valid pointer to an allocated GPIO handle structure. `path` is the GPIO chip character device path. `line` is the GPIO line number. `direction` is one of the direction values enumerated [above](#enumerations).

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_open_name(gpio_t *gpio, const char *path, const char *name, cp_gpio_direction_t direction);
```
Open the character device GPIO with the specified GPIO name and direction at the specified character device GPIO chip path (e.g. `/dev/gpiochip0`).

`gpio` should be a valid pointer to an allocated GPIO handle structure. `path` is the GPIO chip character device path. `line` is the GPIO line name. `direction` is one of the direction values enumerated [above](#enumerations).

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_open_sysfs(gpio_t *gpio, unsigned int line, cp_gpio_direction_t direction);
```
Open the sysfs GPIO with the specified line and direction.

`gpio` should be a valid pointer to an allocated GPIO handle structure. `line` is the Linux GPIO line number. `direction` is one of the direction values enumerated [above](#enumerations).

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int gpio_read(gpio_t *gpio, bool *value);
```
Read the state of the GPIO into `value`.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions. `value` should be a pointer to an allocated bool.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int gpio_write(gpio_t *gpio, bool value);
```
Set the state of the GPIO to `value`.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_poll(gpio_t *gpio, int timeout_ms);
```
Poll a GPIO for the edge event configured with `gpio_set_edge()`.

For character device GPIOs, the edge event should be consumed with `gpio_read_event()`. For sysfs GPIOs, the edge event should be consumed with `gpio_read()`.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions. `timeout_ms` can be positive for a timeout in milliseconds, 0 for a non-blocking poll, or a negative number for a blocking poll.

Returns 1 on success (an edge event occurred), 0 on timeout, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_read_event(gpio_t *gpio, cp_gpio_edge_t *edge, uint64_t *timestamp);
```
Read the edge event that occurred with the GPIO.

This method is intended for use with character device GPIOs and is unsupported by sysfs GPIOs.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions. `timestamp` is event time reported by Linux, in nanoseconds.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int gpio_close(gpio_t *gpio);
```
Close the GPIO.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
void gpio_free(gpio_t *gpio);
```
Free a GPIO handle.

------

```c
int cp_gpio_get_direction(gpio_t *gpio, cp_gpio_direction_t *direction);
int cp_gpio_get_edge(gpio_t *gpio, cp_gpio_edge_t *edge);
```
Query the configured direction or interrupt edge, respectively, of the GPIO.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

```c
int cp_gpio_set_direction(gpio_t *gpio, cp_gpio_direction_t direction);
int cp_gpio_set_edge(gpio_t *gpio, cp_gpio_edge_t edge);
```
Set the direction or interrupt edge, respectively, of the GPIO.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
unsigned int cp_gpio_line(gpio_t *gpio);
```
Return the line the GPIO handle was opened with.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

This function is a simple accessor to the GPIO handle structure and always succeeds.

------

``` c
int cp_gpio_fd(gpio_t *gpio);
```
Return the line file descriptor of the GPIO handle.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

This function is a simple accessor to the GPIO handle structure and always succeeds.

------

``` c
int cp_gpio_name(gpio_t *gpio, char *str, size_t len);
```
Return the line name of the GPIO.

This method is intended for use with character device GPIOs and always returns the empty string for sysfs GPIOs.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_chip_fd(gpio_t *gpio);
```
Return the GPIO chip file descriptor of the GPIO handle.

This method is intended for use with character device GPIOs and is unsupported by sysfs GPIOs.

`gpio` should be a valid pointer to a GPIO handled with one of the `gpio_open*()` functions.

Returns a non-negative file descriptor on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_chip_name(gpio_t *gpio, char *str, size_t len);
```
Return the name of the GPIO chip associated with the GPIO.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_chip_label(gpio_t *gpio, char *str, size_t len);
```
Return the label of the GPIO chip associated with the GPIO.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

Returns 0 on success, or a negative [GPIO error code](#return-value) on failure.

------

``` c
int cp_gpio_tostring(gpio_t *gpio, char *str, size_t len);
```
Return a string representation of the GPIO handle.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `cp_gpio_open*()` functions.

This function behaves and returns like `snprintf()`.

------

``` c
int gpio_errno(gpio_t *gpio);
```
Return the libc errno of the last failure that occurred.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

This function is a simple accessor to the GPIO handle structure and always succeeds.

------

``` c
const char *gpio_errmsg(gpio_t *gpio);
```
Return a human readable error message of the last failure that occurred. The returned string should not be modified by the application.

`gpio` should be a valid pointer to a GPIO handle opened with one of the `gpio_open*()` functions.

This function is a simple accessor to the GPIO handle structure and always succeeds.

### RETURN VALUE

The periphery GPIO functions return 0 on success or one of the negative error codes below on failure.

The libc errno of the failure in an underlying libc library call can be obtained with the `cp_gpio_errno()` helper function. A human readable error message can be obtained with the `gpio_errmsg()` helper function.

| Error Code                        | Description                           |
|-----------------------------------|---------------------------------------|
| `GPIO_ERROR_ARG`                  | Invalid arguments                     |
| `GPIO_ERROR_OPEN`                 | Opening GPIO                          |
| `GPIO_ERROR_NOT_FOUND`            | Line name not found                   |
| `GPIO_ERROR_QUERY`                | Querying GPIO attributes              |
| `GPIO_ERROR_CONFIGURE`            | Configuring GPIO attributes           |
| `GPIO_ERROR_UNSUPPORTED`          | Unsupported attribute or operation    |
| `GPIO_ERROR_INVALID_OPERATION`    | Invalid operation                     |
| `GPIO_ERROR_IO`                   | Reading/writing GPIO                  |
| `GPIO_ERROR_CLOSE`                | Closing GPIO                          |

### EXAMPLE

``` c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gpio.h"

int main(void) {
    gpio_t *gpio_in, *gpio_out;
    bool value;

    gpio_in = gpio_new();
    gpio_out = cp_gpio_new();

    /* Open GPIO /dev/gpiochip0 line 10 with input direction */
    if (gpio_open(gpio_in, "/dev/gpiochip0", 10, GPIO_DIR_IN) < 0) {
        fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpio_in));
        exit(1);
    }

    /* Open GPIO /dev/gpiochip0 line 12 with output direction */
    if (gpio_open(gpio_out, "/dev/gpiochip0", 12, GPIO_DIR_OUT) < 0) {
        fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpio_out));
        exit(1);
    }

    /* Read input GPIO into value */
    if (gpio_read(gpio_in, &value) < 0) {
        fprintf(stderr, "cp_gpio_read(): %s\n", gpio_errmsg(gpio_in));
        exit(1);
    }

    /* Write output GPIO with !value */
    if (gpio_write(gpio_out, !value) < 0) {
        fprintf(stderr, "cp_gpio_write(): %s\n", cp_gpio_errmsg(gpio_out));
        exit(1);
    }

    gpio_close(gpio_in);
    cp_gpio_close(gpio_out);

    gpio_free(gpio_in);
    cp_gpio_free(gpio_out);

    return 0;
}
```

