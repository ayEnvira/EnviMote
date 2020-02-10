// ************************************************************************
// 		EnviMote sample DS3231 
// 	Prints a snapshot of the current date and time along with the UNIX time
// 	Modified by Envira Sostenible from the JeeLabs / Ladyada RTC library examples

#include <Wire.h>
#include "DS3231.h"

RTClib RTC;

void setup () {
    Serial.begin(115200);
    Wire.begin();
}

void loop () {
  
    delay(1000);

// Capture de RTC
    DateTime now = RTC.now();
	
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
// Show Timestamp 
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
}

