
#include "arduinoStringHelper.hpp"
#include "NewLinePortProtocol.hpp"
#include "Esp32WIFISerialNetwork.hpp"

using namespace pankey::Base;
using namespace pankey::Network;
using namespace pankey::ArduinoNetwork;

Esp32WIFISerialNetwork<NewLinePortProtocol,int> network;
int app = 15;

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

  network.addFunctionDelivery(Message);

  network.addFunctionDelivery(Message);

  network.addFunctionDelivery(Message);
  
  network.initialize(app);
  network.onEnable();
}

void loop() {
  network.update(app);
}

void Message(const Message& a_message){
  if(a_message == "cosa" && a_message.getId() == 0){
    network.send("192.168.1.120","cosa");
  }
  Serial.println(i_message);
}
