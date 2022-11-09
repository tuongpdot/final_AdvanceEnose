#include "include/Base_.h"

void sensorBase::get_specification_(sensor_infor handler){ 
  std::cout << "Name:       " << handler.name << std::endl;
  std::cout << "Version:    " << handler.version << std::endl;
  std::cout << "ID:         " << handler.sensor_id << std::endl;
  std::cout << "Type:       " << handler.type << std::endl;
  std::cout << "Max Value:  " << handler.max_value << std::endl;
  std::cout << "Min Value:  " << handler.min_value << std::endl;
  std::cout << "Resolution: " << handler.resolution << std::endl;
  std::cout << "Min Delay:  " << handler.min_delay << std::endl;
}

// void sensorBase::check_state(sensor_flag handler){
//   if( !(handler.Working) ){
//     if(handler.Error) std::cout << "Error occurs" << std::endl;
//     else if(handler.Warning) std::cout << "Some warns occur" << std::endl;
//     else if(handler.Overtime) std::cout << "Overtime occurs" << std::endl;
//     else std::cout << "Flag system has problem! " << std::endl;
//   }
//   else std::cout << "Working flag is On! " << std::endl; 
// }

