#include "C02_sen.h"
#include <stdint.h>

bool sgp30_sen::power_(bool){
  uint8_t cmd_softReset[] = {0x00, 0x06};
  return i2c_handler->write_16bits(0x00, cmd_softReset);
}

bool sgp30_sen::setup_(){

  return true;
}

bool sgp30_sen::configure_(uint8_t){
  
  return true;
}

void sgp30_sen::get_data_(sensor_data &){

}

uint8_t sgp30_sen::get_SerialID(){
  uint8_t* raw_id = i2c_handler->read_16bits(SGP30_FEATURESET);
  /* 
  Check bugs:
  @output: raw_id[0]
  @output: raw_id[1]
  */
  return raw_id[0] << 8 | raw_id[1];
}

bool sgp30_sen::readWordFromCommand(uint16_t command,
                                    uint8_t  commandLength,
                                    uint16_t delayms, uint16_t *readdata,
                                    uint8_t  readlen) {

  uint8_t *data_input = NULL;
  if (!i2c_handler->write_16bits(command, data_input)) {
    return false;
  }

  delay(delayms);

  if (readlen == 0)
    return true;

  uint8_t replylen = readlen * (SGP30_WORD_LEN + 1);
  uint8_t replybuffer[replylen];

  if (!i2c_dev->read(replybuffer, replylen)) {
    return false;
  }

  for (uint8_t i = 0; i < readlen; i++) {
    uint8_t crc = CRC_create(replybuffer + i * 3, 2);
    if (crc != replybuffer[i * 3 + 2])
      return false;
    // success! store it
    readdata[i] = replybuffer[i * 3];
    readdata[i] <<= 8;
    readdata[i] |= replybuffer[i * 3 + 1];
  }
  return true;
}

uint8_t sgp30_sen::CRC_create(uint8_t *data, uint8_t datalength){
  uint8_t crc_cmd = SGP30_CRC8_INIT; 
  for(auto i = 0; i < datalength; i++){
    crc_cmd ^= data[i]; 
    for (auto j = 0; j < 8; j++) {
      if(crc_cmd & 0x80)
        crc_cmd = (crc_cmd) ^ SGP30_CRC8_POLYNOMIAL;  
      else crc_cmd <<= 1;
    }
  }
  return crc_cmd;
}
