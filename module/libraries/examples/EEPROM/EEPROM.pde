#include <EnviMote_24LC256.h>
#include <Wire.h>

EnviMote_24LC256 mem1;  

void setup() {
  
  Serial.begin(9600); // Begin serial communication class
  delay(500);
  mem1.begin();
  Serial.println("EEPROM Test programm. Checking chip...");
  if(mem1.detect()) // Check if eeprom is connected and detectable
  {
    Serial.println("EEPROM 1 detected!");
    eeprom_dump(0, 1000);
  }
  else
  {
    Serial.println("EEPROM 1 not detected!");
  } 
}


void eeprom_dump(int initial_address, int final_address)
{
  if(initial_address<final_address)
  {
      byte read_buffer[final_address-initial_address];
      Serial.print("EEPROM Memory Dump - ");
      Serial.print(initial_address,HEX);
      Serial.print("between");
      Serial.println(final_address);
      Serial.println("----------------------------------");

      mem1.readPage(initial_address,final_address-initial_address,read_buffer);

      for(int i = 0; i<final_address-initial_address ;i++ )
      {
        Serial.print("Memory [");
        Serial.print(initial_address+i,HEX);
        Serial.print("] = ");
        Serial.println(read_buffer[i]);
      }
      
  }
  else
  {
    Serial.println("Dump error!");
  }
}


void loop()
{
}
