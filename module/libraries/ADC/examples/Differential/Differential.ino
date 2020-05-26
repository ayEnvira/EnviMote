#include <Wire.h>
#include <EnviMote_ADS1115.h>

EnviMote_ADS1115 ads;     /* Use thi for the 12-bit version */

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1115
  //                                                                -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.0078125mV
  
  ads.begin();
}

void loop(void)
{
  int16_t results;
  
  /* Be sure to update this value based on the IC and the gain settings! */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = ads.readADC_Differential_0_1();  
  Serial.print("Differential 0-1: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  results = ads.readADC_Differential_2_3();  
  Serial.print("Differential 0-1: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  results = ads.readADC_Differential_4_5();  
  Serial.print("Differential 0-1: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  results = ads.readADC_Differential_6_7();  
  Serial.print("Differential 0-1: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  delay(1000);
}
