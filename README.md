# SDS011Reader

Arduino library that reads data of SDS011 particle sensor. Sending commands to SDS011 is not implemented. Tested with UNO.

To use this library the Serial object must first be initialized in the sketch:

```
Serial.begin(9600);
```
## Functions
- read_data(): Reads the next reading.
- get_avg_reading(_number_of_readings_): Reads _number_of_readings_ and calculates average value.
- pm10(), pm25()
- pm10_avg(), pm25_avg()

## Features
- serial buffer is cleared before reading data (serial buffer can theoretically hold multiple unread readings)
- blocking reading with timeout of 1200 ms
- get_avg_reading() returns after 2 failed readings

## Demo sketch

The demo sketch demonstrates 4 normal readings with read_data() followed by a average reading with get_avg_reading().
