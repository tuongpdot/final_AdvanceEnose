#ifndef C02_SEN_H
#define C02_SEN_H

#include "Base_.h"

#define SGP30_I2CADDR         0x58 ///< SGP30 has only one I2C address

// commands and constants
#define SGP30_FEATURESET      0x0020    ///< The required set for this library
#define SGP30_CRC8_POLYNOMIAL 0x31 ///< Seed for SGP30's CRC polynomial
#define SGP30_CRC8_INIT       0xFF       ///< Init value for CRC
#define SGP30_WORD_LEN        2           ///< 2 bytes per word
#define SGP30_SERIAL_ID       0x3682

using namespace Pipe;

class sgp30_sen : public sensorBase{
  public:
  sgp30_sen(const uint8_t sensor_address) : sensorBase(sensor_address){
    printf("\n");
    get_specification_(SGP30_INFOR);
  }

  // ~sgp30_sen() = default;

  bool power_(bool)           override;

  bool setup_()               override;

  bool configure_(uint8_t)    override;
  
  void get_data_(sensor_data&) override;

  bool read_CRC();

  uint8_t get_SerialID();

  uint8_t CRC_create(uint8_t*, uint8_t);

  private:
    const sensor_infor SGP30_INFOR = {"SGP30",       /* Name       */ 
                                      0x58 ,         /* Address    */ 
                                      1,             /* Version    */ 
                                      99,            /* ID         */ 
                                      CO2_SENSOR,    /* Type       */ 
                                      99.99,         /* Max        */ 
                                      -99.99,        /* Min        */ 
                                      0.999,         /* Resolution */ 
                                      0              /* Min Delay  */
                                     };
};
#endif
