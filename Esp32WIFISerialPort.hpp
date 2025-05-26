
#ifndef Esp32WIFISerialPort_hpp
	#define Esp32WIFISerialPort_hpp

	#include "arduinoStringHelper.hpp"
	#include "ArduinoMemorySize.hpp"
	#include "IPAddress.h"
	#include "SerialPort.hpp"
	#include "WiFi.h"

	#if defined(pankey_Log) && (defined(Esp32WIFISerialPortn_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoNetwork_Log))
		#include "Logger_status.hpp"
		#define Esp32WIFISerialPortLog(status,method,mns) pankey_Log(status,"Esp32WIFISerialPort",method,mns)
	#else
		#define Esp32WIFISerialPortLog(status,method,mns)
	#endif

	namespace pankey{

		namespace ArduinoNetwork{

			class Esp32WIFISerialPort : public Network::SerialPort<String,String>{	
				public:
					Esp32WIFISerialPort(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}
					
					Esp32WIFISerialPort(String a_name){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", a_name);
						m_name = a_name;
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Esp32WIFISerialPort(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Destructor", "");
						if(this->connected()){
							this->stop();
						}
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					Esp32WIFISerialPort(const Esp32WIFISerialPort& a_serialport){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
						m_client = a_serialport.m_client;
						m_name = a_serialport.m_name;
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Esp32WIFISerialPort(WiFiClient a_client){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", "eclient");
						m_client = a_client;
						m_name = "eclient";
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Esp32WIFISerialPort(WiFiClient a_client, String a_name){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "Contructor", a_name);
						m_client = a_client;
						m_name = a_name;
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual int status(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "status", "");
						// return m_client.status();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "status", "");
						return 0;
					}

					virtual int available(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "available", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "available", "");
						return m_client.available();
					}

					virtual int read(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "read", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "read", "");
						return m_client.read();
					}

					virtual String readln(float a_time){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "readln", "");
						String i_message;
						long i_time_limit = 1000 * a_time;
						long i_start_time = millis();
						Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "time limit:");
						Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", i_time_limit);
						Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "start limit:");
						Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", i_start_time);
						while ((millis() - i_start_time) < i_time_limit) {
							Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "while is running");
							if(this->available() != 0){
								char i_capture = (char)this->read();
								Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "char capture:");
								Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", i_capture);
								if(i_capture == '\n'){
									Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "note capture:");
									Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", i_message);
									return i_message;
								}
								Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", "adding char to note:");
								Esp32WIFISerialPortLog(pankey_Log_Statement, "readln", i_message);
								i_message = concat(i_message, i_capture);
								// Watchdog::feed();
							}
						}
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "readln", "");
						return "";
					}

					virtual int peek(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "peek", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "peek", "");
						return m_client.peek();
					}

					virtual Base::memory_size write(int chr){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "write", chr);
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "write", "");
						return m_client.write(chr);
					}

					virtual Base::memory_size write(uint8_t chr){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "write", chr);
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "write", "");
						return m_client.write(chr);
					}

					virtual bool connected(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connected", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connected", "");
						return m_client.connected();
					}
					
					virtual bool connect(const String& a_address){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connect", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connect", "");
						return connect(a_address, -1);
					}
					
					virtual bool connect(const String& a_address, int port){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "connect", "");
						
						IPAddress ip = toIPAddress(a_address);
						
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "connect", "");
						return m_client.connect(ip, port);
					}
					
					virtual void stop(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "stop", "");
						m_client.stop();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "stop", "");
					}

					virtual void flush(){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "flush", "");
						m_client.flush();
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "flush", "");
					}
					
					virtual Base::memory_size print(String s){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "print", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "print", "");
						return m_client.print(s);
					}
					
					virtual Base::memory_size println(String s){
						Esp32WIFISerialPortLog(pankey_Log_StartMethod, "println", "");
						Esp32WIFISerialPortLog(pankey_Log_EndMethod, "println", "");
						return m_client.println(s);
					}

					virtual void operator=(const Esp32WIFISerialPort& a_serialport){
						m_client = a_serialport.m_client;
					}

					virtual bool operator==(const Esp32WIFISerialPort& a_serialport){
						return m_client == a_serialport.m_client;
					}

					virtual bool operator!=(const Esp32WIFISerialPort& a_serialport){
						return m_client != a_serialport.m_client;
					}

					virtual operator bool(){
						return m_client;
					}

				protected:
					WiFiClient m_client;
			};

		}

	}

#endif