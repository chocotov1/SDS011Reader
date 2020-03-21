#ifndef SDS011READER 
#define SDS011READER

#include <Arduino.h>

class SDS011Reader {
   public:
      SDS011Reader();
      uint16_t pm10_int;
      uint16_t pm25_int;
      uint16_t pm10_int_avg;
      uint16_t pm25_int_avg;

      bool read_data();
      bool process_serial();
      bool get_avg_reading(uint8_t = 4);

      float pm10();
      float pm25();
      float pm10_avg();
      float pm25_avg();
};

#endif
