#include <Adafruit_VEML7700.h>
#include <DHT_U.h>
#include <DHT.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(8, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(9600); //A0
  // Serial1.begin(115200); // baud rate for lux sensor

  // set up light sensor
  // while (!Serial) { 
  //   delay(10); 
  // }
  // Serial.println("Adafruit VEML7700 Test");
  // if (!veml.begin()) {
  //  Serial.println("Sensor not found");
  //  while (1);
  // }
  // Serial.println("Sensor found");
  // veml.setLowThreshold(10000);
  // veml.setHighThreshold(20000);
  // veml.interruptEnable(true);

  // set up dht and soil sensor
  dht.begin();
  delay(100);

  Serial.println("Setup Success!"); 
}

void loop() {
  delay(1000);
  Serial.println(dht.readHumidity());

}
