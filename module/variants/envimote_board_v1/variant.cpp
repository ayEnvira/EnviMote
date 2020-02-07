/*
  Copyright (c) 2015 Atmel Corp./Thibaut VIARD. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | Serial           |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          |                  |  PB23  | RX0             | RX CONSOLE/EXTINT(7)
 * | 1          |                  |  PB22  | TX0             | TX CONSOLE/EXINT(6)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTB,  23, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, // RX: SERCOM5/PAD[3]
  { PORTB,  22, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // TX: SERCOM5/PAD[2]

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | Digital          |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 2          |                  |  PA28  | PWM2            | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 3          |                  |  PA27  | PWM3            | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 4          |                  |  PA25  | PWM4            | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 5          |                  |  PA24  | PWM5            | EIC/EXTINT[7]  ADC/AIN[15]  PTC/Y[13
 * | 6          |                  |  PA15  | PWM6            | EIC/EXTINT[4]  ADC/AIN[12]  PTC/Y[10]
 * | 7          |                  |  PA14  | PWM7            | EIC/EXTINT[5]  ADC/AIN[13]  PTC/Y[11]
 * | 8          |                  |  PA19  | PWM8            | EIC/EXTINT[4]  PTC/X[8]  SERCOM5/PAD[2]  SERCOM3_ALT/PAD[2]  TC7/WO[0]  TCC0_ALT/WO[6]  I2S/SCK[0]  GCLK_IO[4]
 * | 9          |                  |  PA18  | PWM9            | EIC/EXTINT[5]  PTC/X[9]  SERCOM5/PAD[3]  SERCOM3_ALT/PAD[3]  TC7/WO[1]  TCC0_ALT/WO[7]  I2S/FS[0]  GCLK_IO[5]
 * | 10         |                  |  PA11  | PWM10           | EIC/EXTINT[14]  PTC/X[14]  SERCOM4/PAD[2]  TC5/WO[0]  GCLK_IO[0]
 * | 11         |                  |  PA10  | PWM11           | EIC/EXTINT[15]  PTC/X[15]  SERCOM4/PAD[3]  TC5/WO[1]  GCLK_IO[1]
 * | 12         |                  |  PB14  | PWM12           | EIC/EXTINT[14]  SERCOM5_ALT/PAD[0]  TCC0/WO[0]  TCC1_ALT/WO[2]
 * | 13         |                  |  PB12  | PWM13           | EIC/EXTINT[15]  SERCOM2/PAD[3]  SERCOM4_ALT/PAD[3]  TC3/WO[1]  TCC0_ALT/WO[5]  GCLK_IO[1]
 * | 14         |                  |  PA16  | SDA1            | EIC/EXTINT[8]  GCLK_IO[0]
 * | 15         |                  |  PA17  | SCL1            | EIC/EXTINT[15]  GCLK_IO[0]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 },
  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },
  { PORTA, 25, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC5_CH1, EXTERNAL_INT_13 },
  { PORTA, 24, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC5_CH0, EXTERNAL_INT_12 },
  { PORTA, 15, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH1, EXTERNAL_INT_15 },
  { PORTA, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH0, EXTERNAL_INT_14 },
  { PORTA, 19, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH1, EXTERNAL_INT_3 },
  { PORTA, 18, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH0, EXTERNAL_INT_2 },
  { PORTA, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC1_CH1, EXTERNAL_INT_11 },
  { PORTA, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC1_CH0, EXTERNAL_INT_10 },
  { PORTB, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC5_CH0, EXTERNAL_INT_14 },
  { PORTB, 12, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH0, EXTERNAL_INT_12 },
  { PORTA, 16, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC2_CH0, EXTERNAL_INT_0 }, // RX: SERCOM1/PAD[1]
  { PORTA, 17, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC2_CH1, EXTERNAL_INT_1 }, // TX: SERCOM1/PAD[0]

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | Analog pins      |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 16         |                  |  PA02  | A0/EXT1_3       | 
 * | 17         |                  |  PB08  | A1/EXT1_4       | 
 * | 18         |                  |  PB09  | A2/EXT2_3       | 
 * | 19         |                  |  PA04  | A3/EXT2_4       | 
 * | 20         |                  |  PA05  | A4/EXT3_3       | 
 * | 21         |                  |  PA06  | A5/EXT3_4       | 
 * | 22         |                  |  PA07  | A6/EXT3_4       | 
 * | 23         |                  |  PB00  | A7/EXT3_4       | 
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // ADC/AIN[8]
  { PORTB,  8, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_TIMER), ADC_Channel1, NOT_ON_PWM, TC4_CH0, EXTERNAL_INT_8 }, // ADC/AIN[9]
  { PORTB,  9, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_TIMER), ADC_Channel2, NOT_ON_PWM, TC4_CH1, EXTERNAL_INT_9 }, // ADC/AIN[18]
  { PORTA,  4, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel3, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_4 }, // ADC/AIN[19]
  { PORTA,  5, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel4, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 }, // ADC/AIN[0] and also DAC/VOUT
  { PORTA,  6, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel5, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_6 }, // ADC/AIN[1]
  { PORTA,  7, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel6, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7 }, // ADC/AIN[0] and also DAC/VOUT
  { PORTB,  0, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_TIMER), ADC_Channel7, NOT_ON_PWM, TC7_CH0, EXTERNAL_INT_0 }, // ADC/AIN[0] and also DAC/VOUT

/*
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | Communication    |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 24         |                  |  PA09  | SCL             | SERCOM0/PAD[1]
 * | 25         |                  |  PA08  | SDA             | SERCOM0/PAD[0]
 * | 26         |                  |  PA13  | RX1             | SERCOM2/PAD[1]
 * | 27         |                  |  PA12  | TX1             | SERCOM2/PAD[0]
 * | 28         |                  |  PA23  | RX2             | SERCOM3/PAD[1]
 * | 29         |                  |  PA22  | TX2             | SERCOM3/PAD[0]
 * | 30         |                  |  PA17  | RX3/SCL1        | SERCOM1/PAD[1]
 * | 31         |                  |  PA16  | TX3/SDA1        | SERCOM1/PAD[0]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTA,  9, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_9 }, // SCL: SERCOM0/PAD[1]
  { PORTA,  8, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_NMI }, // SDA: SERCOM0/PAD[0]
  { PORTA, 13, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_12 }, // RX: SERCOM2/PAD[1]
  { PORTA, 12, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_13 }, // TX: SERCOM2/PAD[0]
  { PORTA, 23, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC4_CH1, EXTERNAL_INT_7 }, // RX: SERCOM3/PAD[1]
  { PORTA, 22, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC4_CH0, EXTERNAL_INT_6 }, // TX: SERCOM3/PAD[0]
  { PORTA, 17, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC2_CH1, EXTERNAL_INT_1 }, // RX: SERCOM1/PAD[1]
  { PORTA, 16, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC2_CH0, EXTERNAL_INT_0 }, // TX: SERCOM1/PAD[0]

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | SPI              |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 32         |                  |  PB10  | MOSI/EXT1_16    | SERCOM4_ALT/PAD[2]
 * | 33         |                  |  PB13  | MISO/EXT1_17    | SERCOM4_ALT/PAD[1]
 * | 34         |                  |  PB11  | SCK/EXT1_18     | SERCOM4_ALT/PAD[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTB, 10, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, // SERCOM4_ALT/PAD[2]
  { PORTB, 13, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM4_CH1, NOT_ON_TIMER, EXTERNAL_INT_13 }, // SERCOM4_ALT/PAD[1]
  { PORTB, 11, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // SERCOM4_ALT/PAD[3]


/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | LEDs & button    |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 35         | N/A              |  PB03  | LED0            | 
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTB, 3, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC6_CH1, EXTERNAL_INT_3}, // TCC0/WO[0]

/* +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | Pin number | Digital          |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 36         |                  |  PB04  | EXT3/DIG22      | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 37         |                  |  PB05  | EXT5/DIG24      | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 38         |                  |  PB06  | EXT7/DIG26      | EIC/EXTINT[6]  ADC/AIN[14]  PTC/Y[12]
 * | 39         |                  |  PB07  | EXT9/DIG28      | EIC/EXTINT[7]  ADC/AIN[15]  PTC/Y[13
 * | 40         |                  |  PB14  | EXT11/DIG30     | EIC/EXTINT[4]  ADC/AIN[12]  PTC/Y[10]
 * | 41         |                  |  PB15  | EXT13/DIG32     | EIC/EXTINT[5]  ADC/AIN[13]  PTC/Y[11]
 * | 42         |                  |  PA14  | EXT15/DIG34     | EIC/EXTINT[4]  PTC/X[8]  SERCOM5/PAD[2]  SERCOM3_ALT/PAD[2]  TC7/WO[0]  TCC0_ALT/WO[6]  I2S/SCK[0]  GCLK_IO[4]
 * | 43         |                  |  PA15  | EXT17/DIG36     | EIC/EXTINT[5]  PTC/X[9]  SERCOM5/PAD[3]  SERCOM3_ALT/PAD[3]  TC7/WO[1]  TCC0_ALT/WO[7]  I2S/FS[0]  GCLK_IO[5]
 * | 44         |                  |  PB16  | EXT19/DIG38     | EIC/EXTINT[14]  PTC/X[14]  SERCOM4/PAD[2]  TC5/WO[0]  GCLK_IO[0]
 * | 45         |                  |  PB17  | EXT21/DIG40     | EIC/EXTINT[15]  PTC/X[15]  SERCOM4/PAD[3]  TC5/WO[1]  GCLK_IO[1]
 * | 46         |                  |  PA20  | EXT23/DIG42     | EIC/EXTINT[14]  SERCOM5_ALT/PAD[0]  TCC0/WO[0]  TCC1_ALT/WO[2]
 * | 47         |                  |  PA21  | EXT25/DIG44     | EIC/EXTINT[15]  SERCOM2/PAD[3]  SERCOM4_ALT/PAD[3]  TC3/WO[1]  TCC0_ALT/WO[5]  GCLK_IO[1]
 * | 48         |                  |  PB30  | EXT27/DIG46     | EIC/EXTINT[8]  GCLK_IO[0]
 * | 49         |                  |  PB31  | EXT29/DIG48     | EIC/EXTINT[15]  GCLK_IO[0]
 * | 50         |                  |  PB01  | EXT31/DIG50     | EIC/EXTINT[15]  GCLK_IO[0]
 * | 51         |                  |  PB02  | EXT33/DIG52     | EIC/EXTINT[15]  GCLK_IO[0]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 */
  { PORTB, 04, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 },
  { PORTB, 05, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },
  { PORTB, 06, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 },
  { PORTB, 07, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },
  { PORTB, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH0, TC5_CH0, EXTERNAL_INT_14 },
  { PORTB, 15, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH1, TC5_CH1, EXTERNAL_INT_15 },
  { PORTA, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH0, EXTERNAL_INT_14 },
  { PORTA, 15, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC3_CH1, EXTERNAL_INT_15 },
  { PORTB, 16, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC6_CH0, EXTERNAL_INT_0 },
  { PORTB, 17, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC6_CH1, EXTERNAL_INT_1 },
  { PORTA, 20, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM7_CH0, TC7_CH0, EXTERNAL_INT_4 },
  { PORTA, 21, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM7_CH1, TC7_CH1, EXTERNAL_INT_5 },
  { PORTB, 30, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC0_CH0, EXTERNAL_INT_14 },
  { PORTB, 31, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TCC0_CH0, EXTERNAL_INT_15 },
  { PORTB, 01, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, TC7_CH0, EXTERNAL_INT_1 },
  { PORTB, 02, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM6_CH0, TC7_CH1, EXTERNAL_INT_2 },

};

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5, TC6, TC7 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial( &sercom5, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX ) ;

void SERCOM5_Handler(void)
{
  Serial.IrqHandler();
}

Uart Serial1( &sercom2, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;

void SERCOM2_Handler(void)
{
  Serial1.IrqHandler();
}


Uart Serial2( &sercom3, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX ) ;

void SERCOM3_Handler(void)
{
  Serial2.IrqHandler();
}

Uart Serial3( &sercom1, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX ) ;

void SERCOM1_Handler(void)
{
  Serial3.IrqHandler();
}
