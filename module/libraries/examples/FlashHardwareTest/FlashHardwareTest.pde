#include <EnviMote_SerialFlash.h>
#include <SPI.h>

const int FlashChipSelect = 2; // digital pin for flash chip CS pin

EnviMote_SerialFlash SerialFlash;

const unsigned long testIncrement = 4096;

void setup() {

  Serial.begin(9600);

  while (!Serial) ;
    delay(100);

  Serial.println("Raw SerialFlash Hardware Test");
  SerialFlash.begin(FlashChipSelect); // proceed even if begin() fails

  if (test()) {
    Serial.println();
    Serial.println("All Tests Passed  :-)");
    Serial.println();
    Serial.println("Test data was written to your chip.  You must run");
    Serial.println("EraseEverything before using this chip for files.");
  } else {
    Serial.println();
    Serial.println("Tests Failed  :{");
    Serial.println();
    Serial.println("The flash chip may be left in an improper state.");
    Serial.println("You might need to power cycle to return to normal.");
  }
}


bool test() {
  unsigned char buf[256], sig[256], buf2[8];
  unsigned long address, count, chipsize, blocksize;
  unsigned long usec;
  bool first;

  // Read the chip identification
  Serial.println();
  Serial.println("Read Chip Identification:");
  SerialFlash.readID(buf);
  Serial.print("  JEDEC ID:     ");
  Serial.print(buf[0], HEX);
  Serial.print(" ");
  Serial.print(buf[1], HEX);
  Serial.print(" ");
  Serial.println(buf[2], HEX);
  Serial.print("  Part Nummber: ");
  Serial.println(id2chip(buf));
  Serial.print("  Memory Size:  ");
  chipsize = SerialFlash.capacity(buf);
  Serial.print(chipsize);
  Serial.println(" bytes");
  if (chipsize == 0) return false;
  Serial.print("  Block Size:   ");
  blocksize = SerialFlash.blockSize();
  Serial.print(blocksize);
  Serial.println(" bytes");

  SerialFlash.eraseAll();

  // Read the entire chip.  Every test location must be
  // erased, or have a previously tested signature
  Serial.println();
  Serial.println("Reading Chip...");
  memset(buf, 0, sizeof(buf));
  memset(sig, 0, sizeof(sig));
  memset(buf2, 0, sizeof(buf2));
  address = 0;
  count = 0;
  first = true;
  while (address < chipsize) {
    SerialFlash.read(address, buf, 8);
//    Serial.print("  addr = ");
//    Serial.print(address, HEX);
//    Serial.print(", data = ");
//    printbuf(buf, 8);
    create_signature(address, sig);
    if (is_erased(buf, 8) == false) {
      if (equal_signatures(buf, sig) == false) {
        Serial.print("  Previous data found at address ");
        Serial.println(address);
        Serial.println("  You must fully erase the chip before this test");
        Serial.print("  found this: ");
        printbuf(buf, 8);
        Serial.print("     correct: ");
        printbuf(sig, 8);
        Serial.println("Erasing block... ");
        return false;
      }
    } else {
      count = count + 1; // number of blank signatures
    }
    if (first) {
      address = address + (testIncrement - 8);
      first = false;
    } else {
      address = address + 8;
      first = true;
    }
  }


  // Write any signatures that were blank on the original check
  if (count > 0) {
    Serial.println();
    Serial.print("Writing ");
    Serial.print(count);
    Serial.println(" signatures");
    memset(buf, 0, sizeof(buf));
    memset(sig, 0, sizeof(sig));
    memset(buf2, 0, sizeof(buf2));
    address = 0;
    first = true;
    while (address < chipsize) {
      SerialFlash.read(address, buf, 8);
      if (is_erased(buf, 8)) {
        create_signature(address, sig);
//        Serial.print("write ");
//        Serial.print(address);
//        Serial.print(": data: ");
//        printbuf(sig, 8);
        SerialFlash.write(address, sig, 8);
        while (!SerialFlash.ready()) ; // wait
        SerialFlash.read(address, buf, 8);
        if (equal_signatures(buf, sig) == false) {
          Serial.print("  error writing signature at ");
          Serial.println(address);
          Serial.print("  Read this: ");
          printbuf(buf, 8);
          Serial.print("  Expected:  ");
          printbuf(sig, 8);
          return false;
        }
      }
      if (first) {
        address = address + (testIncrement - 8);
        first = false;
      } else {
        address = address + 8;
        first = true;
      }
    }
  } else {
    Serial.println("  all signatures present from prior tests");
  }


  // Read all the signatures again, just to be sure
  // checks prior writing didn't corrupt any other data
  Serial.println();
  Serial.println("Double Checking All Signatures:");
  memset(buf, 0, sizeof(buf));
  memset(sig, 0, sizeof(sig));
  memset(buf2, 0, sizeof(buf2));
  count = 0;
  address = 0;
  first = true;
  while (address < chipsize) {
    SerialFlash.read(address, buf, 8);
    create_signature(address, sig);
    if (equal_signatures(buf, sig) == false) {
      Serial.print("  error in signature at ");
      Serial.println(address);
      Serial.print("  Read this: ");
      printbuf(buf, 8);
      Serial.print("  Expected:  ");
      printbuf(sig, 8);
      return false;
    }
    count = count + 1;
    if (first) {
      address = address + (testIncrement - 8);
      first = false;
    } else {
      address = address + 8;
      first = true;
    }
  }
  Serial.print("  all ");
  Serial.print(count);
  Serial.println(" signatures read ok");


  // Read pairs of adjacent signatures
  // check read works across boundaries
  Serial.println();
  Serial.println("Checking Signature Pairs");
  memset(buf, 0, sizeof(buf));
  memset(sig, 0, sizeof(sig));
  memset(buf2, 0, sizeof(buf2));
  count = 0;
  address = testIncrement - 8;
  first = true;
  while (address < chipsize - 8) {
    SerialFlash.read(address, buf, 16);
    create_signature(address, sig);
    create_signature(address + 8, sig + 8);
    if (memcmp(buf, sig, 16) != 0) {
      Serial.print("  error in signature pair at ");
      Serial.println(address);
      Serial.print("  Read this: ");
      printbuf(buf, 16);
      Serial.print("  Expected:  ");
      printbuf(sig, 16);
      return false;
    }
    count = count + 1;
    address = address + testIncrement;
  }
  Serial.print("  all ");
  Serial.print(count);
  Serial.println(" signature pairs read ok");


  return true;
}


void loop() {
  // do nothing after the test
}

const char * id2chip(const unsigned char *id)
{
	if (id[0] == 0x1F) {
		// Atmel
		if (id[1] == 0x47) {
			if (id[2] == 0x00) return "AT25SF Ver.0";
			if (id[2] == 0x01) return "AT25SF Ver.1";
		}
	}
	return "(unknown chip)";
}

void print_signature(const unsigned char *data)
{
	Serial.print("data=");
	for (unsigned char i=0; i < 8; i++) {
		Serial.print(data[i]);
		Serial.print(" ");
	}
	Serial.println();
}

void create_signature(unsigned long address, unsigned char *data)
{
	data[0] = address >> 24;
	data[1] = address >> 16;
	data[2] = address >> 8;
	data[3] = address;
	unsigned long hash = 2166136261ul;
	for (unsigned char i=0; i < 4; i++) {
		hash ^= data[i];
		hash *= 16777619ul;
	}
	data[4] = hash;
	data[5] = hash >> 8;
	data[6] = hash >> 16;
	data[7] = hash >> 24;
}

bool equal_signatures(const unsigned char *data1, const unsigned char *data2)
{
	for (unsigned char i=0; i < 8; i++) {
		if (data1[i] != data2[i]) return false;
	}
	return true;
}

bool is_erased(const unsigned char *data, unsigned int len)
{
	while (len > 0) {
		if (*data++ != 255) return false;
		len = len - 1;
	}
	return true;
}


void printbuf(const void *buf, uint32_t len)
{
  const uint8_t *p = (const uint8_t *)buf;
  do {
    unsigned char b = *p++;
    Serial.print(b >> 4, HEX);
    Serial.print(b & 15, HEX);
    //Serial.printf("%02X", *p++);
    Serial.print(" ");
  } while (--len > 0);
  Serial.println();
}

void waitforchar(void)
{
  while (Serial.read() == -1);
}
