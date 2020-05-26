#include <Wire.h>
#include <EnviMote_ADS1115.h>

EnviMote_ADS1115 ads;     /* Use the ADC */

void setup(void) 
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..7");
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
  int16_t adc0, adc1, adc2, adc3;
  int16_t adc4, adc5, adc6, adc7;

  digitalWrite(LED_BUILTIN, LOW);
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  adc4 = ads.readADC_SingleEnded(4);
  adc5 = ads.readADC_SingleEnded(5);
  adc6 = ads.readADC_SingleEnded(6);
  adc7 = ads.readADC_SingleEnded(7);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.print("AIN4: "); Serial.println(adc4);
  Serial.print("AIN5: "); Serial.println(adc5);
  Serial.print("AIN6: "); Serial.println(adc6);
  Serial.print("AIN7: "); Serial.println(adc7);
  Serial.println(" ");
  
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(1000);
}
