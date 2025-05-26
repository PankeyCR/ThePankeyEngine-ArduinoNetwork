
#include "arduinoStringHelper.hpp"
#include "Esp32WIFIConnection.hpp"
#include "Esp32WIFISerialServer.hpp"

using namespace pankey::Base;
using namespace pankey::Network;
using namespace pankey::ArduinoNetwork;

Esp32WIFISerialServer server;
ArrayRawPointerMap<SerialPort<String,String>,String> ports;
ArrayRawPointerList<SerialPort<String,String>> diconnection;

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("start");

  diconnection.setOwner(false);

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

  server.begin();
}

void loop() {
  auto i_port = server.accept();
  if(i_port != nullptr){
    Serial.println("connection done");
    ports.addPointer(i_port.get());
    i_port.release();
    Serial.println(ESP.getFreeHeap());
  }
  for(int x = 0; x < ports.length(); x++){
    auto f_port = ports.getPointerByIndex(x);
    if(f_port == nullptr){
      continue;
    }
    if(!f_port->connected()){
      Serial.println("connection lost");
      diconnection.addPointer(f_port);
      Serial.println(ESP.getFreeHeap());
      continue;
    }
    if(f_port->available() > 0){
      char f_read = f_port->read();
      Serial.print("Data input: ");
      Serial.println(f_read);

    }
  }
  if(!diconnection.isEmpty()){
    Serial.println("connection removed");
    ports.destroyFromList(diconnection);
    diconnection.reset();
    Serial.println(ESP.getFreeHeap());
  }
}
