#include <Adafruit_VEML7700.h>
#include <DHT_U.h>
#include <DHT.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

#define DHTTYPE DHT22  // DHT 22  (AM2302)
DHT dht(8, DHTTYPE);   //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(9600);     //A0
  // Serial1.begin(9600);  // baud rate for lux sensor

  // set up light sensor
  // while (!Serial1) {
  while (!Serial) {
    delay(10);
  }
  // Serial.println("Adafruit VEML7700 Test");
  if (!veml.begin()) {
    Serial.println("Sensor not found");
    while (1)
      ;
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

  dht.begin();         // setup dht
  pinMode(A0, INPUT);  // setup soil sensor

  delay(100);

  Serial.println("Setup Success!");
}

void loop() {
  delay(1000);

  /* READ HUMIDITY SENSOR */
  int humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(humidity);


  /* READ LUX SENSOR */
  // Serial.print("raw ALS: "); Serial.println(veml.readALS());
  // Serial.print("raw white: "); Serial.println(veml.readWhite());
  int lux = veml.readLux();
  Serial.print("Lux: ");
  Serial.println(lux);

  // uint16_t irq = veml.interruptStatus();
  // if (irq & VEML7700_INTERRUPT_LOW) {
  //   Serial.println("** Low threshold");
  // }
  // if (irq & VEML7700_INTERRUPT_HIGH) {
  //   Serial.println("** High threshold");
  // }

  /* READ MOISTURE SENSOR */
  int moisture = analogRead(A0);
  Serial.print("Moisture: ");
  Serial.println(moisture);

  if (moisture >= 1000) {
    Serial.println("Sensor is not in the Soil or DISCONNECTED");
  }
  if (moisture < 1000 && moisture >= 600) {
    Serial.println("Soil is DRY");
  }
  if (moisture < 600 && moisture >= 370) {
    Serial.println("Soil is HUMID");
  }
  if (moisture < 370) {
    Serial.println("Sensor in WATER");
  }
}
