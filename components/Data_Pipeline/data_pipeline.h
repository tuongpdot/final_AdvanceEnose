#ifndef DATA_PIPELINE_H
#define DATA_PIPELINE_H
#pragma once

#include <sys/_stdint.h>
#include <iostream>
#include <vector>

#include "cppi2c.h"
#include "driver/i2c.h"

#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "freertos/portmacro.h"

namespace Pipe
{
  class Data_Monitor{
    public:
    bool virtual data_isValid() = 0;

    bool virtual data_isStored() = 0;
  };

  class i2c_protocol : public Data_Monitor{ 
    public:
    i2c_protocol(CPPI2C::I2c *i2c, uint8_t sensor_addr):i2c_(i2c), sen_addr_(sensor_addr)/* , sensor_here(ptr) */{};

    ~i2c_protocol();

    bool data_isValid() override;

    bool data_isStored() override;

    bool write_toByte(const uint8_t, const uint8_t);

    uint8_t read_toByte(const uint8_t);

    bool write_16bits(const uint16_t, uint8_t*);

    uint8_t* read_16bits(const uint16_t);

    bool read_multiByte(const uint8_t, uint8_t*, const int);

  private:
    CPPI2C::I2c *i2c_;
    const uint8_t sen_addr_;
  }; // class I2c
} // namespace CPPI2C

#endif // !DATA_PIPELINE_H
