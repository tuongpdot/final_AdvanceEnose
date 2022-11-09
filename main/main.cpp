#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "C02_sen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cppi2c.h"

#include "data_pipeline.h"
#include "Temp_sen.h"

constexpr static int I2C_SDA = 21;
constexpr static int I2C_SCL = 22;
constexpr static uint32_t I2C_CLK_SPEED_HZ = 400000;

CPPI2C::I2c i2c {I2C_NUM_0};

extern "C" void app_main(void)
{
  /* I2c global declaration: */
  i2c.InitMaster(I2C_SDA, I2C_SCL, I2C_CLK_SPEED_HZ, true, true);

  /* Sensor declaration: */
  sensor_data data_Sen; 
  temper_sensor i2c_temp(0x18);
  sgp30_sen i2c_CO2(0x58);

  printf("\n");

  if( i2c_temp.power_(1) && (!i2c_temp.power_(0)) ){
    std::cout << "Sensor Restart Completed! " << std::endl; 
  }

  i2c_temp.configure_(3);

  if(i2c_temp.setup_()){
    printf("Resolution: %d \n", i2c_temp.get_resolution_());
  }

  uint8_t co2ID = i2c_CO2.get_SerialID();
  printf("co2ID: %d", co2ID);

  printf("\n");

  while(true){
    i2c_temp.get_data_(data_Sen);
    std::cout << "Temperature: " << data_Sen.value << " oC" << std::endl;
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

