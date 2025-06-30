
#ifndef IP_hpp
	#define IP_hpp

	#include "ByteArray.hpp"

	namespace pankey{

		namespace ArduinoNetwork{

			Base::ByteArray toIP(const String& a_mac){
				Base::ByteArray i_mac;
				i_mac.createArray(4);
				String i_note;
				for(int x = 0; x < a_mac.length(); x++){
					char f_char = a_mac.charAt(x);
					if(f_char == '.'){
						Byte i_value = i_note.toInt();
						i_mac.add(i_value);
						i_note = "";
						continue;
					}
					i_note += f_char;
				}
				if(!i_note.isEmpty()){
					uint8_t i_value = i_note.toInt();
					i_mac.add(i_value);
				}
				return i_mac;
			}
		}
	}

#endif
