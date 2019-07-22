#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "revpi.h"

static void piControlOpen(revpi_peripheral *revpi);
static void piControlClose(revpi_peripheral *revpi);
static int piControlRead(revpi_peripheral *revpi, uint8_t *data);
static int piControlWrite(revpi_peripheral *revpi, uint8_t *data);
static int piControlGetVariableInfo(revpi_peripheral *revpi);
static int piControlGetDeviceInfo(revpi_peripheral *revpi);

static bool opened = false;

/* Private functions */

static int piControlGetVariableInfo(revpi_peripheral *revpi) {
  int ret;
  if (revpi->pi_control_fd < 0)
    return -ENODEV;

  ret = ioctl(revpi->pi_control_fd, KB_FIND_VARIABLE, &revpi->variable);

  return ret;
}

static int piControlGetDeviceInfo(revpi_peripheral* revpi) {
  int ret = 0;
  if (revpi->pi_control_fd < 0)
    return -ENODEV;

ret = ioctl(revpi->pi_control_fd, KB_GET_DEVICE_INFO, &revpi->device_info);
if (ret < 0)
    return ret;

  return 0;
}

static void piControlOpen(revpi_peripheral *revpi) {
  static int fd = 0;

  if (!opened) {
    fd = open(PICONTROL_DEVICE, O_RDWR);
    if (fd > 0) {
        opened = true;
    } else {
        printf("Open failed:%d \n", fd);
    }
  }
  revpi->pi_control_fd = fd;
}

static void piControlClose(revpi_peripheral *revpi) {
  if (revpi->pi_control_fd > 0) {
    close(revpi->pi_control_fd);
    opened = false;
  }
}

static int piControlRead(revpi_peripheral *revpi, uint8_t *data) {
  int ret = 0;
  if (revpi->pi_control_fd < 0)
    return -ENODEV;

  if (revpi->variable.i16uLength == 1) {
    revpi->value.i16uAddress += revpi->value.i8uBit >> 3;
    revpi->value.i8uBit %= 8;
    ret = ioctl(revpi->pi_control_fd, KB_GET_VALUE, &revpi->value);
    *data = revpi->value.i8uValue;
    if (ret < 0)
      return ret;
  } else if (revpi->variable.i16uLength == 8 ||
             revpi->variable.i16uLength == 16 ||
             revpi->variable.i16uLength == 32) {
    ret = lseek(revpi->pi_control_fd, revpi->variable.i16uAddress, SEEK_SET);
    if (ret < 0)
      return ret;
    ret = read(revpi->pi_control_fd, data, (revpi->variable.i16uLength >> 3));
    if (ret < 0)
      return ret;
  }
  return ret;
}

static int piControlWrite(revpi_peripheral *revpi, uint8_t *data) {
  int ret = 0;

  if (revpi->pi_control_fd < 0)
    return -ENODEV;
  if (revpi->variable.i16uLength == 1) {
    revpi->value.i8uValue = *data;
    revpi->value.i16uAddress += (revpi->value.i8uBit >> 3);
    revpi->value.i8uBit %= 8;
    ret = ioctl(revpi->pi_control_fd, KB_SET_VALUE, &revpi->value);
    if (ret < 0)
      return ret;
  } else if (revpi->variable.i16uLength == 8 ||
             revpi->variable.i16uLength == 16 ||
             revpi->variable.i16uLength == 32) {
    ret = lseek(revpi->pi_control_fd, revpi->variable.i16uAddress, SEEK_SET);
    if (ret < 0)
      return ret;
    ret = write(revpi->pi_control_fd, data, (revpi->variable.i16uLength >> 3));
    if (ret < 0)
      return ret;
  }
  return ret;
}

/* Public functions */

int revpi_init(revpi_peripheral *revpi) {
  int ret = 0;

  piControlOpen(revpi);
  strncpy(revpi->variable.strVarName, revpi->pin_name, sizeof(revpi->variable.strVarName));
  piControlGetDeviceInfo(revpi); /* Optional info */
  ret = piControlGetVariableInfo(revpi);
  revpi->value.i8uValue = 0;
  revpi->value.i16uAddress = revpi->variable.i16uAddress;
  revpi->value.i8uBit = revpi->variable.i8uBit;

  return ret;
}

int revpi_set_do_level(revpi_peripheral *revpi, uint8_t level) {
  int ret = 0;

  ret = piControlWrite(revpi, &level);
  if (ret > 0)
    return ret;
  else
    return -1;
}

int revpi_exit(revpi_peripheral *revpi) {
    piControlClose(revpi);
    return 0;
}

int revpi_get_di_level(revpi_peripheral *revpi) {
  uint8_t level = 0;
  if (piControlRead(revpi, &level) == 0)
    return level;
  return -1;
}

int revpi_set_do_push_pull(revpi_peripheral *revpi, uint16_t push_pull) {
    uint8_t push_pull_t[2] = {push_pull & 0xFF, push_pull >> 8};

    return piControlWrite(revpi, push_pull_t);
}

int revpi_get_ai_value(revpi_peripheral *revpi) {
    uint8_t value = 0;
    if (piControlRead(revpi, &value) == 0)
      return value;
    return -1;
}
