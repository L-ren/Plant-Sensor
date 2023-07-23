#include <Adafruit_VEML7700.h>
#include <DHT_U.h>
#include <DHT.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(8, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(9600); //A0
  Serial1.begin(115200); // baud rate for lux sensor

  // set up light sensor
  while (!Serial1) { 
    delay(10); 
  }
  Serial.println("Adafruit VEML7700 Test");
  if (!veml.begin()) {
   Serial.println("Sensor not found");
   while (1);
  }
  Serial.println("Sensor found");
  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);
  /*
   // == OPTIONAL =====
 // Can set non-default gain and integration time to
 // adjust for different lighting conditions.
 // =================
 // veml.setGain(VEML7700_GAIN_1_8);
 // veml.setIntegrationTime(VEML7700_IT_100MS);
 Serial.print(F("Gain: "));
 switch (veml.getGain()) {
  case VEML7700_GAIN_1: Serial.println("1"); break;
  case VEML7700_GAIN_2: Serial.println("2"); break;
  case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
  case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
 }
  Serial.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime()) {
   case VEML7700_IT_25MS: Serial.println("25"); break;
   case VEML7700_IT_50MS: Serial.println("50"); break;
   case VEML7700_IT_100MS: Serial.println("100"); break;
   case VEML7700_IT_200MS: Serial.println("200"); break;
   case VEML7700_IT_400MS: Serial.println("400"); break;
   case VEML7700_IT_800MS: Serial.println("800"); break;
 }
  */ 

  // set up dht and soil sensor
  dht.begin();
  delay(100);

  Serial.println("Setup Success!"); 
}

void loop() {
  delay(1000);
  Serial.println(dht.readHumidity());

}
