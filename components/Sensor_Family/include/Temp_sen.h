#ifndef TEMP_SEN_H
#define TEMP_SEN_H

#include "Base_.h"

#define MCP9808_I2CADDR   0x18   ///< I2C address
#define MCP9808_CONFIG    0x01   ///< MCP9808 config register

#define MCP9808_CONFIG_SHUTDOWN   0x0100 ///< shutdown config
#define MCP9808_CONFIG_CRITLOCKED 0x0080 ///< critical trip lock
#define MCP9808_CONFIG_WINLOCKED  0x0040 ///< alarm window lock
#define MCP9808_CONFIG_INTCLR     0x0020 ///< interrupt clear
#define MCP9808_CONFIG_ALERTSTAT  0x0010 ///< alert output status
#define MCP9808_CONFIG_ALERTCTRL  0x0008 ///< alert output control
#define MCP9808_CONFIG_ALERTSEL   0x0004 ///< alert output select
#define MCP9808_CONFIG_ALERTPOL   0x0002 ///< alert output polarity
#define MCP9808_CONFIG_ALERTMODE  0x0001 ///< alert output mode

#define MCP9808_UPPER_TEMP        0x02   ///< upper alert boundary
#define MCP9808_LOWER_TEMP        0x03   ///< lower alert boundery
#define MCP9808_CRIT_TEMP         0x04   ///< critical temperature
#define MCP9808_AMBIENT_TEMP      0x05   ///< ambient temperature
#define MCP9808_MANUF_ID          0x06   ///< manufacture ID 00000000 01010100
#define MCP9808_DEVICE_ID         0x07   ///< device ID 00000100 0000000
#define MCP9808_RESOLUTION        0x08   ///< resolutin 00000011

using namespace Pipe;

class temper_sensor : public sensorBase{
public:
  temper_sensor(const uint8_t sensor_address):sensorBase(sensor_address){
    printf("\n");
    get_specification_(MCP9808_Infor);
  }

  // ~temper_sensor() = default;

  bool power_(bool)           override;

  bool setup_()               override;

  bool configure_(uint8_t)    override;
  
  void get_data_(sensor_data&) override;

  uint8_t get_resolution_();
  
private:
  const sensor_infor MCP9808_Infor = {"MCP9808",     /* Name       */ 
                                      0x18 ,         /* Address    */ 
                                      1,             /* Version    */ 
                                      9808,          /* ID         */ 
                                      TEMP_SENSOR,   /* Type       */ 
                                      100.0,         /* Max        */ 
                                      -20.0,         /* Min        */ 
                                      0.0625,        /* Resolution */ 
                                      0              /* Min Delay  */
                                     };
};

#endif /* SENSOR_BASE_H */
