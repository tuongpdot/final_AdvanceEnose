#include "Temp_sen.h"

bool temper_sensor::setup_(){

  /* MANUF_ID register verify ID */
  data_ptr = i2c_handler->read_16bits(MCP9808_MANUF_ID);
  if( data_ptr[1] != 84){
    return false;
  }

  /* DEVICE_IF register verify ID */
  data_ptr = i2c_handler->read_16bits(MCP9808_DEVICE_ID);
  if( data_ptr[0] != 4){
    return false;
  }

  /*BUG: 
   @brief:  write to register 
   @return: failed 
   @tested: byte/16bits 
            - works for other function 
  */
  // uint8_t config_write = 0x0;
  // uint8_t* ptr = &config_write; 
  // printf("writeToConfig: %d\n", i2c_handler->write_16bits(MCP9808_CONFIG, ptr));
  // if ((i2c_handler->write_16bits(MCP9808_CONFIG, ptr)) == 0 ){
  //   return false;
  // }

  std::cout << "MCP9808 Setup SUCCESSED!" << std::endl;
  return true;
}

bool temper_sensor::configure_(uint8_t resolution_arg){
  return i2c_handler->write_toByte(MCP9808_RESOLUTION, resolution_arg & 0x03);
}

uint8_t temper_sensor::get_resolution_(){
  return i2c_handler->read_toByte(MCP9808_RESOLUTION);
}

bool temper_sensor::power_(bool turnOff ){
  uint8_t cmd_shutdown; 
  uint8_t* cmd_register = i2c_handler->read_16bits(MCP9808_CONFIG);

  if(turnOff){
    cmd_shutdown = cmd_register[0] | MCP9808_CONFIG_SHUTDOWN;
    i2c_handler->write_toByte(MCP9808_CONFIG, cmd_shutdown);
    return true; /* Turn off successfully */
  }
  else if (!turnOff){
    cmd_shutdown = cmd_register[0] & ~MCP9808_CONFIG_SHUTDOWN;
    i2c_handler->write_toByte(MCP9808_CONFIG, cmd_shutdown);
    return false; /* Being in Continuous conversion */
  }
  return false;   /* Being in Continuous coversion */
}

void temper_sensor::get_data_(sensor_data& handler){
  uint8_t* raw_temp = i2c_handler->read_16bits(MCP9808_AMBIENT_TEMP);

  /* check flag */
  if((raw_temp[0] & 0x80) == 0x80){/* printf("0x80: cleared\n"); */}
  if((raw_temp[0] & 0x40) == 0x40){/* printf("0x40: cleared\n"); */}
  if((raw_temp[0] & 0x20) == 0x20){/* printf("0x20: cleared\n"); */}

  raw_temp[0] = raw_temp[0] & 0x1F;

  /* convert to Temp based on Datasheet */
  if((raw_temp[0] & 0x10) == 0x10){
    raw_temp[0] = raw_temp[0] & 0x10;
    handler.value = 256 - ((double)(raw_temp[0] * 16) + (double)(raw_temp[1] / 16.0));
  }else{
    handler.value = ((double)(raw_temp[0] * 16) + (double)(raw_temp[1] / 16.0));
  }
}
