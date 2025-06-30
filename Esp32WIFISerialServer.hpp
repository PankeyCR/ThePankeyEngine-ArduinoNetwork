
#ifndef Esp32WIFISerialServer_hpp
	#define Esp32WIFISerialServer_hpp

	#include "SerialServer.hpp"
	#include "SerialPort.hpp"
	#include "Esp32WIFISerialPort.hpp"
	#include "unique_ptr.hpp"

	#include "WiFi.h"

	#if defined(pankey_Log) && (defined(Esp32WIFISerialServer_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
		#include "Logger_status.hpp"
		#define Esp32WIFISerialServerLog(status,method,mns) pankey_Log(status,"Esp32WIFISerialServer",method,mns)
	#else
		#define Esp32WIFISerialServerLog(status,method,mns)
	#endif
	
	namespace pankey{

		namespace ArduinoNetwork{

			class Esp32WIFISerialServer : public Network::SerialServer{	
				public:
					Esp32WIFISerialServer():server(80){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(80)");
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					Esp32WIFISerialServer(int port):server(port){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(port)");
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					Esp32WIFISerialServer(const Esp32WIFISerialServer& a_wifi_server){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Contructor", "server(port)");
						server = a_wifi_server.server;
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					
					virtual ~Esp32WIFISerialServer(){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.stop();
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void begin(){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.begin();
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void stop(){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "Destructor", "");
						server.stop();
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual Base::unique_ptr<Network::SerialPort> accept(){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "accept", "");
						Esp32WIFISerialServerLog(pankey_Log_Statement, "accept", "pankey_GENERIC_ESP32");
						WiFiClient client = server.accept();   // Listen for incoming clients
						if(client){
							Base::unique_ptr<Network::SerialPort> i_port = new Esp32WIFISerialPort(client);
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "if(client)");
							return i_port;
						}
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
						return nullptr;
					} 
					
					virtual Base::unique_ptr<Network::SerialPort> available(){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "available", "");
						WiFiClient client = server.available();   // Listen for incoming clients
						if(client){
							Base::unique_ptr<Network::SerialPort> i_port = new Esp32WIFISerialPort(client);
							Esp32WIFISerialServerLog(pankey_Log_EndMethod, "available", "if(client)");
							return i_port;
						}
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "accept", "return nullptr");
						return nullptr;
					}
					
					virtual void operator=(const Esp32WIFISerialServer& a_wifi_server){
						Esp32WIFISerialServerLog(pankey_Log_StartMethod, "operator=", "server(port)");
						server = a_wifi_server.server;
						Esp32WIFISerialServerLog(pankey_Log_EndMethod, "operator=", "");
					}

				protected:
					WiFiServer server;
			};

		}

	}

#endif