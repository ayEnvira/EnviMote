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

#ifndef _VARIANT_ATMEL_SAMD21_XPRO_
#define _VARIANT_ATMEL_SAMD21_XPRO_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK		    (48000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"
#include <stdbool.h>

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (50ul)
#define NUM_DIGITAL_PINS     (28ul)
#define NUM_ANALOG_INPUTS    (8ul)
#define NUM_ANALOG_OUTPUTS   (0ul)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// Interrupts
#define digitalPinToInterrupt(P)   ( g_APinDescription[P].ulExtInt )

// LED(s)
#define PIN_LED_13           (35ul)
#define PIN_LED              PIN_LED_13
#define PIN_LED0             PIN_LED_13
#define LED_BUILTIN          PIN_LED_13

/*
 * Analog pins
 */
#define PIN_A0               (16ul)
#define PIN_A1               (17ul)
#define PIN_A2               (18ul)
#define PIN_A3               (19ul)
#define PIN_A4               (20ul)
#define PIN_A5               (21ul)
#define PIN_A6               (22ul)
#define PIN_A7               (23ul)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
static const uint8_t A4  = PIN_A4 ;
static const uint8_t A5  = PIN_A5 ;
static const uint8_t A6  = PIN_A6 ;
static const uint8_t A7  = PIN_A7 ;
#define ADC_RESOLUTION		12

/*
 * Serial interfaces
 */
// Serial (Console)
#define PIN_SERIAL_RX       (0ul)
#define PIN_SERIAL_TX       (1ul)
#define PAD_SERIAL_RX       (SERCOM_RX_PAD_3)
#define PAD_SERIAL_TX       (UART_TX_PAD_2)

// Serial1
#define PIN_SERIAL1_RX       (26ul)
#define PIN_SERIAL1_TX       (27ul)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)

// Serial2
#define PIN_SERIAL2_RX       (28ul)
#define PIN_SERIAL2_TX       (29ul)
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_1)
#define PAD_SERIAL2_TX       (UART_TX_PAD_0)

// Serial3
#define PIN_SERIAL3_RX       (30ul)
#define PIN_SERIAL3_TX       (31ul)
#define PAD_SERIAL3_RX       (SERCOM_RX_PAD_1)
#define PAD_SERIAL3_TX       (UART_TX_PAD_0)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

#define PIN_SPI_MOSI         (32ul)
#define PIN_SPI_MISO         (33ul)
#define PIN_SPI_SCK          (34ul)
#define PIN_SPI_SS           (13ul)
#define PERIPH_SPI           sercom4
#define PAD_SPI_TX           SPI_PAD_2_SCK_3
#define PAD_SPI_RX           SERCOM_RX_PAD_0

static const uint8_t SS	  = PIN_SPI_SS ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

#define PIN_SPI1_MOSI         (52ul)
#define PIN_SPI1_MISO         (53ul)
#define PIN_SPI1_SCK          (54ul)
#define PIN_SPI1_SS           (7ul)
#define PERIPH_SPI1           sercom2
#define PAD_SPI1_TX           SPI_PAD_0_SCK_3
#define PAD_SPI1_RX           SERCOM_RX_PAD_1

static const uint8_t SS1	= PIN_SPI1_SS ;
static const uint8_t MOSI1 	= PIN_SPI1_MOSI ;
static const uint8_t MISO1 	= PIN_SPI1_MISO ;
static const uint8_t SCK1  	= PIN_SPI1_SCK ;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#define PIN_WIRE_SCL         (24ul)
#define PIN_WIRE_SDA         (25ul)
#define PERIPH_WIRE          sercom0
#define WIRE_IT_HANDLER      SERCOM0_Handler

#define PIN_WIRE1_SCL         (30ul)
#define PIN_WIRE1_SDA         (31ul)
#define PERIPH_WIRE1          sercom1
#define WIRE1_IT_HANDLER      SERCOM1_Handler

/*
 * USB
 */
#define PIN_USB_DP           (0ul)
#define PIN_USB_DM           (0ul)
#define PIN_USB_HOST_ENABLE  (0ul)
#define PIN_USB_VBUS         PIN_USB_HOST_ENABLE
#define PIN_USB_ID           (0ul)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
 */
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;

extern Uart Serial;
extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial3;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      Serial
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif /* _VARIANT_ATMEL_SAMD21_XPRO_ */

