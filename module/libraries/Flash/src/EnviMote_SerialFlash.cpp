/**************************************************************************/
/*!
    File:     SerialFlash.cpp: AT25DFxxx Flash library
    Author:   Envira Sostenible
    License:  BSD (see license.txt)

    Driver for AT25DFxxx Serial flash memory

    v1.0 - First release
*/
/**************************************************************************/

#include "EnviMote_SerialFlash.h"
#include "SPI.h"

#define SPICONFIG   SPISettings(4000000, MSBFIRST, SPI_MODE0)


// Constructor
EnviMote_SerialFlash::EnviMote_SerialFlash(void) {
}

#define ID0_ATMEL		0x1F

// Initial the class
bool EnviMote_SerialFlash::begin(uint8_t pin)
{
	uint8_t id[5];
	uint8_t f;
	uint32_t size;

	dirindex = 0;
	flags = 0;
	busy = 0;

	// Initialization the SPI port and chip select pin
	SPI.begin();
	chipSelectPin=pin;
	pinMode(pin, OUTPUT);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	
	// Wake up the chip and read de ID
	wakeup();
	readID(id);
	if ((id[0]==0 && id[1]==0 && id[2]==0) || (id[0]==255 && id[1]==255 && id[2]==255)) {
		Serial.println("ERROR");
		return false;
	}
	f = 0;
	size = capacity(id);
	flags = f;
	readID(id);
	return true;
}

// wait routine. It has a timeout counter to allow an exit
void EnviMote_SerialFlash::wait(void)
{
	uint32_t status;
	int16_t cntTimeout=10;
	while (cntTimeout-->0) {
		SPI.beginTransaction(SPICONFIG);
		digitalWrite(chipSelectPin, SS_ACTIVE);
		// all others work by simply reading the status reg
		SPI.transfer(CMD_STATUS);
		status = SPI.transfer(0);
		digitalWrite(chipSelectPin, SS_DEACTIVE);
		SPI.endTransaction();
		if (!(status & 1)) break;
		delayMicroseconds(1);

	}
	if (cntTimeout>0)
		busy = 0;
	else
		busy = 1;
}

// Read bytes from Flash
void EnviMote_SerialFlash::read(uint32_t addr, void *buf, uint32_t len)
{
	uint8_t *p = (uint8_t *)buf;
	uint8_t b, f, status, cmd;

	memset(p, 0, len);
	f = flags;
	SPI.beginTransaction(SPICONFIG);
	wait();
	do {
		uint32_t rdlen = len;
		digitalWrite(chipSelectPin, SS_ACTIVE);
		// TODO: FIFO optimize....
		SPI.transfer(CMD_READ);
		SPI.transfer((addr >> 16) & 255);
		SPI.transfer16(addr);
		SPI.transfer(0);		// Dummy
		SPI.transfer(p, rdlen);
		digitalWrite(chipSelectPin, SS_DEACTIVE);
		p += rdlen;
		addr += rdlen;
		len -= rdlen;
	} while (len > 0);
	SPI.endTransaction();
}

// Write bytes from Flash
void EnviMote_SerialFlash::write(uint32_t addr, const void *buf, uint32_t len)
{
	const uint8_t *p = (const uint8_t *)buf;
	uint32_t max, pagelen;
	uint32_t aux_addr;

	aux_addr=addr;
	SPI.beginTransaction(SPICONFIG);
	wait();
	do {
		digitalWrite(chipSelectPin, SS_ACTIVE);
		// Unprotect sector
		SPI.transfer(CMD_UNPROTECT_SECTOR);
		SPI.transfer((addr >> 16) & 0xFF);
		SPI.transfer16(addr);
		digitalWrite(chipSelectPin, SS_DEACTIVE);
		delayMicroseconds(1);

		digitalWrite(chipSelectPin, SS_ACTIVE);
		// write enable command
		SPI.transfer(CMD_WRITE_ENABLE);
		digitalWrite(chipSelectPin, SS_DEACTIVE);
		delayMicroseconds(1);

		max = 256 - (addr & 0xFF);
		pagelen = (len <= max) ? len : max;
		delayMicroseconds(1); 
		digitalWrite(chipSelectPin, SS_ACTIVE);
		SPI.transfer(CMD_WRITE); // program page command
		SPI.transfer((addr >> 16) & 255);
		SPI.transfer16(addr);
		addr += pagelen;
		len -= pagelen;
		do {
			SPI.transfer(*p++);
		} while (--pagelen > 0);
		digitalWrite(chipSelectPin, SS_DEACTIVE);
		SPI.endTransaction();
	} while (len > 0);

	digitalWrite(chipSelectPin, SS_ACTIVE);
	// Protect sector
	SPI.transfer(CMD_PROTECT_SECTOR);
	SPI.transfer((aux_addr >> 16) & 0xFF);
	SPI.transfer16(aux_addr);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
}

// Erase chip
void EnviMote_SerialFlash::eraseAll()
{
	wait();
	// All other chips support the bulk erase command
	SPI.beginTransaction(SPICONFIG);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	// write enable command
	SPI.transfer(CMD_WRITE_ENABLE);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	delayMicroseconds(1);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	// bulk erase command
	SPI.transfer(CMD_ERASE_ALL);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	SPI.endTransaction();
}

// Erase block
void EnviMote_SerialFlash::eraseBlock(uint32_t addr)
{
	wait();
	SPI.beginTransaction(SPICONFIG);
	// Unprotect sector
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_UNPROTECT_SECTOR);
	SPI.transfer((addr >> 16) & 0xFF);
	SPI.transfer16(addr);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	delayMicroseconds(1);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_WRITE_ENABLE); // write enable command
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	delayMicroseconds(1);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_ERASE_BLOCK);
	SPI.transfer((addr >> 16) & 255);
	SPI.transfer16(addr);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	delayMicroseconds(1);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_PROTECT_SECTOR);
	SPI.transfer((addr >> 16) & 0xFF);
	SPI.transfer16(addr);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	SPI.endTransaction();
}


bool EnviMote_SerialFlash::ready()
{
	uint32_t status;
	
	SPI.beginTransaction(SPICONFIG);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	// all others work by simply reading the status reg
	SPI.transfer(CMD_STATUS);
	status = SPI.transfer(0);
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	SPI.endTransaction();
	//Serial.printf("ready=%02x\n", status & 0xFF);
	if ((status & 1)) 
		return false;
	else
		return true;
}


// chips tested: https://github.com/PaulStoffregen/SerialFlash/pull/12#issuecomment-169596992
//
void EnviMote_SerialFlash::sleep()
{
	wait();
	SPI.beginTransaction(SPICONFIG);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_SLEEP); // Deep power down command
	digitalWrite(chipSelectPin, SS_DEACTIVE);
}

void EnviMote_SerialFlash::wakeup()
{
	SPI.beginTransaction(SPICONFIG);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_WAKEUP); // Wake up from deep power down command
	digitalWrite(chipSelectPin, SS_DEACTIVE);
}

void EnviMote_SerialFlash::readID(uint8_t *buf)
{
	wait();
	SPI.beginTransaction(SPICONFIG);
	digitalWrite(chipSelectPin, SS_ACTIVE);
	SPI.transfer(CMD_READ_ID);
	buf[0] = SPI.transfer(0); // manufacturer ID
	buf[1] = SPI.transfer(0); // memory type
	buf[2] = SPI.transfer(0); // Version
	digitalWrite(chipSelectPin, SS_DEACTIVE);
	SPI.endTransaction();
}


uint32_t EnviMote_SerialFlash::capacity(const uint8_t *id)
{
	uint32_t n = 1048576; // unknown chips, default to 1 MByte

	if (id[2] >= 16 && id[2] <= 31) {
		n = 1ul << id[2];
	} else
	if (id[2] >= 32 && id[2] <= 37) {
		n = 1ul << (id[2] - 6);
	} else
	if ((id[0]==0 && id[1]==0 && id[2]==0) || 
		(id[0]==255 && id[1]==255 && id[2]==255)) {
		n = 0;
	}
	//Serial.printf("capacity %lu\n", n);
	return n;
}

uint32_t EnviMote_SerialFlash::blockSize()
{
	// everything else seems to have 4K sectors
	return 4096;
}

