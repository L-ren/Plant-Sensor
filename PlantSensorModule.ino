#include <SPI.h>
#include <WiFiNINA.h>
#include <Adafruit_VEML7700.h>
#include <DHT_U.h>
#include <DHT.h>
#include "config.h" // "" for custom header files

char ssid[] = WIFI_SSID;        // network SSID (name)
char pass[] = WIFI_PW;    // network password (use for WPA, or use as key for WEP)
// int keyIndex = 0;            // network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS), reduces sketch size
char server[] = "www.google.com";    // name address for Google (using DNS)

// Initialize Ethernet client library with IP address and port of the server
// port 80 is default for HTTP
WiFiClient client;

Adafruit_VEML7700 veml = Adafruit_VEML7700();

#define DHTTYPE DHT22  // DHT 22  (AM2302)
DHT dht(8, DHTTYPE);   //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(9600); // A0
  while (!Serial) {
    ; // wait for serial port to connect, for native USB port only
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
  
  dht.begin();         // setup dht
  pinMode(A0, INPUT);  // setup soil sensor

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
  // if connected, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
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

  // if there are incoming bytes available
  // from the server, read them and print them:
  // while (client.available()) {
  //   char c = client.read();
  //   Serial.write(c);
  // }

  if (client.available()) {
    Serial.println("connected to server");
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    while (true);
  }


}

void printWifiStatus() {
  // print the SSID of the network:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print  board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}