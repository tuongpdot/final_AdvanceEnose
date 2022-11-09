#ifndef BASE_H
#define BASE_H

#include <sys/_stdint.h>
#include <vector>

#include "data_pipeline.h"

using namespace Pipe; 

typedef enum {
  CO2_SENSOR,
  MOX_SENSOR,
  TEMP_SENSOR,
  COULOUR_SENSOR,
}sensor_type;

typedef struct{
  std::string name;        /**< sensor name */
  uint8_t sensor_home_ADR; /**< sensor address */
  int version;             /**< version of the hardware + driver */
  int sensor_id;           /**< unique sensor identifier */
  sensor_type type;        /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
  float max_value;         /**< maximum value of this sensor's value in SI units */
  float min_value;         /**< minimum value of this sensor's value in SI units */
  float resolution;        /**< smallest difference between two values */
  int min_delay;           /**< min delay in microseconds between events/ 
                                zero = not a constant rate */
}sensor_infor; 

typedef struct{
  float value;
}sensor_data; 

class sensorBase {

public:
  /* */
  sensorBase(const uint8_t sensor_address) : sensor_address_(sensor_address){
    i2c_handler = new i2c_protocol(&i2c_Available, sensor_address);
    printf("Sensor Address: %d \n", sensor_address_);
  };

  /* */
  ~sensorBase(){
    std::cout << "Base class destructed! " << std::endl;
  } ;

  virtual bool setup_() = 0;

  virtual bool configure_(uint8_t) = 0;

  virtual bool power_(bool) = 0;

  virtual void get_data_(sensor_data&) = 0;

  void get_specification_(sensor_infor);

protected:
  i2c_protocol *i2c_handler;
  uint8_t *data_ptr; 
  
private:
  const uint8_t sensor_address_;
  CPPI2C::I2c i2c_Available{I2C_NUM_0}; 
};

#endif /* SENSOR_BASE_H */
