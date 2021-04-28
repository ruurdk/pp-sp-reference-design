/*
Copyright (c) 2021 Jan Marjanovic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <stdio.h>
#include <unistd.h>

#include "altera_avalon_i2c.h"

#include "mini_i2cdetect.h"

void mini_i2cdetect(ALT_AVALON_I2C_DEV_t *i2c_dev, uint16_t start_addr,
                    uint16_t stop_addr) {
  uint8_t rx_buf[1];
  alt_printf(" %04x | ", 0);
  for (int i = 0; i < (start_addr % 16); i++) {
    alt_printf("   ");
  }

  for (int addr = start_addr; addr < stop_addr; addr++) {
    if ((addr % 16) == 0) {
      alt_printf("\n %04x | ", addr);
    }

    alt_avalon_i2c_master_target_set(i2c_dev, addr);
    ALT_AVALON_I2C_STATUS_CODE rc = alt_avalon_i2c_master_receive(
        i2c_dev, rx_buf, 1, ALT_AVALON_I2C_NO_RESTART, ALT_AVALON_I2C_STOP);
    if (rc == ALT_AVALON_I2C_SUCCESS) {
      alt_printf("%02x ", addr);
    } else {
      alt_printf("-- ");
    }
    usleep(1000);
  }
  alt_printf("\n");
}
