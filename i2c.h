#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

uint8_t i2c_init(const char *device, int addr);
uint8_t i2c_close();
uint8_t i2c_read(uint8_t reg, uint8_t *buf, size_t len);
uint8_t i2c_write(uint8_t reg, uint8_t val);

#endif