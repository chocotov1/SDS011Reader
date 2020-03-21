#include <SDS011Reader.h>

SDS011Reader sds011;

void setup() {
  Serial.begin(9600);
}

void print_read_data(){
  if (sds011.read_data()){
     /*
     Serial.print(F("pm10_int: "));
     Serial.println(sds011.pm10_int);
     Serial.print(F("pm25_int: "));
     Serial.println(sds011.pm25_int);
     */
    
     Serial.print(F("pm10: "));
     Serial.println(sds011.pm10(), 1);
     Serial.print(F("pm25: "));
     Serial.println(sds011.pm25(), 1);

  } else {
     Serial.println(F("read_data failed.."));
  }
}

void print_avg_reading(uint8_t number_of_readings = 3){
  Serial.print(F("start get_avg_reading("));
  Serial.print(number_of_readings);
  Serial.println(F(").."));

  if (sds011.get_avg_reading(number_of_readings)){
    /*
    Serial.print(F("pm10_int_avg: "));
    Serial.println(sds011.pm10_int_avg);
    Serial.print(F("pm25_int_avg: "));
    Serial.println(sds011.pm25_int_avg);
    */
    
    Serial.print(F("pm10_avg: "));
    Serial.println(sds011.pm10_avg(), 1);
    Serial.print(F("pm25_avg: "));
    Serial.println(sds011.pm25_avg(), 1);
  } else {
     Serial.println(F("get_avg_reading failed.."));
  }
}

void loop() {
  for (uint8_t i = 0; i < 4; i++){
    print_read_data();
  }

  print_avg_reading(3);
}
