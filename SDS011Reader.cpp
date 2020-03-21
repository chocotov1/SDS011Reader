#include <SDS011Reader.h>

SDS011Reader::SDS011Reader(){}

bool SDS011Reader::read_data(){
   // clear serial buffer (no old data):
   while (Serial.available()) Serial.read();

   uint32_t reading_timeout = millis() + 1200;

   while (millis() < reading_timeout){
      if (process_serial()){
         // retry many times until valid data was processed 
         return true;
      }
   }

   return false;
}

bool SDS011Reader::process_serial(){
   // SDS011_laser_PM2.5_sensor_specification-V1.3.pdf
   // See section "The UART communication protocol" on page 5

   if (Serial.available() < 10){
      return false;
   }

   pm10_int = 0;
   pm25_int = 0;

   // checksum_total overflows but that doesn't matter for the check
   uint8_t checksum_total        = 0;
   uint8_t checksum_byte_sds011  = 0;

   for (int i = 0; i < 10; i++){
      uint8_t sds011_byte = Serial.read(); 
      if (i >= 2 && i <= 7){
         checksum_total += sds011_byte;
      }
      
      if (i == 0 && sds011_byte != 0xAA){
         return false;
      } else if (i == 1 && sds011_byte != 0xC0){
         return false;
      } else if (i == 2){
         pm25_int = sds011_byte;
      } else if (i == 3){
         pm25_int += sds011_byte<<8;
      } else if (i == 4){
         pm10_int = sds011_byte;
      } else if (i == 5){
         pm10_int += sds011_byte<<8;
      } else if (i == 8){
         checksum_byte_sds011 = sds011_byte;
      } else if (i == 9 && sds011_byte != 0xAB){
         return false;
      }
   }

   if (checksum_total != checksum_byte_sds011){
      //Serial.println(F("checksum error"));
      return false;
   }

   //Serial.println(F("checksum ok"));
   return true;
}

bool SDS011Reader::get_avg_reading(uint8_t number_of_readings){
   uint16_t avg_reading_pm25_total = 0;
   uint16_t avg_reading_pm10_total = 0;
   uint8_t  ok_readings            = 0;
   const uint8_t max_failed        = 2;
   uint8_t  failed                 = 0;

   while (ok_readings < number_of_readings){
      if (read_data()){
         avg_reading_pm25_total += pm25_int;
         avg_reading_pm10_total += pm10_int;
         ok_readings++;
         //Serial.println(F("ok reading.."));
      } else {
          failed++;
      }

      if (failed >= max_failed){
         pm25_int_avg = 0;
         pm10_int_avg = 0;
         return false;
      }
   }

   pm25_int_avg = avg_reading_pm25_total / number_of_readings;
   pm10_int_avg = avg_reading_pm10_total / number_of_readings;
   return true;
}

float SDS011Reader::pm10(){
   return pm10_int / 10.0;
}

float SDS011Reader::pm25(){
   return pm25_int / 10.0;
}

float SDS011Reader::pm10_avg(){
   return pm10_int_avg / 10.0;
}

float SDS011Reader::pm25_avg(){
   return pm25_int_avg / 10.0;
}
