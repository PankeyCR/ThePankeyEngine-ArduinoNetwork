
#include "arduinoStringHelper.hpp"
#include "Esp32WIFIConnection.hpp"

using namespace pankey::ArduinoNetwork;

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("start");


  initializeWIFI( "10.10.10.10.10.150"  ,     //mac
                  "192.168.1.140"       ,     //ip
                  "192.168.1.1"         ,     //gateway
                  "192.168.1.1"         ,     //subnet
                  "255.255.255.0"       ,     //dns
                  "MERCUSYS_6541"       ,     //router name
                  "57924106");                //router password

                  //router name MERCUSYS_6541 - pokemon - Cristo
                  //router password 57924106 - tania1919 - Jesucristo#1

  haltUntilWIFIConnection();
}

void loop() {
  Serial.println(hasWifiLAN());
}
