/* SerialFlash Library - for filesystem-like access to SPI Serial Flash memory
 * https://github.com/PaulStoffregen/SerialFlash
 * Copyright (C) 2015, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this library was funded by PJRC.COM, LLC by sales of Teensy.
 * Please support PJRC's efforts to develop open source software by purchasing
 * Teensy or other genuine PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SerialFlash_h_
#define SerialFlash_h_

#include <Arduino.h>
#include <SPI.h>

#define SS_ACTIVE	LOW
#define SS_DEACTIVE	HIGH

#define	CMD_READ				0x0B
#define CMD_WRITE				0x02
#define CMD_ERASE_BLOCK			0x20
#define	CMD_ERASE_ALL			0x60
#define	CMD_STATUS				0x05
#define	CMD_WRITE_ENABLE		0x06
#define	CMD_PROTECT_SECTOR		0x36
#define	CMD_UNPROTECT_SECTOR	0x39
#define CMD_SLEEP				0xB9
#define	CMD_WAKEUP				0xAB
#define CMD_READ_ID				0x9F

class EnviMote_SerialFlash
{
public:
	EnviMote_SerialFlash(void);
	bool begin(uint8_t pin = 2);
	uint32_t capacity(const uint8_t *id);
	uint32_t blockSize();
	void sleep();
	void wakeup();
	void readID(uint8_t *buf);
	void read(uint32_t addr, void *buf, uint32_t len);
	bool ready();
	void wait();
	void write(uint32_t addr, const void *buf, uint32_t len);
	void eraseAll();
	void eraseBlock(uint32_t addr);

private:
	uint8_t	chipSelectPin;
	uint16_t dirindex; // current position for readdir()
	uint8_t flags;	// chip features
	uint8_t busy;	// 0 = ready
				// 1 = suspendable program operation
				// 2 = suspendable erase operation
				// 3 = busy for realz!!
};

#endif
