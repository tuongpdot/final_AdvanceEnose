#include <iostream>
#include <sys/_stdint.h>

#include "data_pipeline.h"

using namespace Pipe;

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
bool i2c_protocol::data_isValid(){
  return false;
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
bool i2c_protocol::data_isStored(){
  return false;
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
bool i2c_protocol::write_toByte(const uint8_t register_adr, const uint8_t data){
  return i2c_->WriteRegister(sen_addr_, register_adr, data);
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
bool i2c_protocol::write_16bits(const uint16_t register_adr, uint8_t* data){
  return i2c_->WriteRegisterMultipleBytes(sen_addr_, register_adr, data, 2);
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
uint8_t i2c_protocol::read_toByte(const uint8_t register_adr){
  return i2c_->ReadRegister(sen_addr_, register_adr);
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
uint8_t* i2c_protocol::read_16bits(const uint16_t register_adr){
  static uint8_t dou_bytes[2]; /* Keep dou_bytes not die out of scope */
  i2c_->ReadRegisterMultipleBytes(sen_addr_, register_adr, dou_bytes, 2);
  return dou_bytes;
}

/* 
 *@brief: Interface for i2c_protocol  
 *@desire: Import sensor's class -> I2C -> {Sensor, I2c} 
 *@arg 
 */
bool i2c_protocol::read_multiByte(const uint8_t reg_adr_, uint8_t *buffer, const int length){
  return i2c_->ReadRegisterMultipleBytes(sen_addr_, reg_adr_, buffer, length);
} 
