/**
 * Arduino - A simple resource implementation
 * 
 * SimpleExternlaEepromResourceIO.h
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_H__
#define __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_H__ 1

#include <ExternalEeprom.h>
#include <ResourceSystem.h>

class ExternalEepromResourceSystem: public ResourceSystem {

private:
    ExternalEeprom* eeprom;

public:

    ExternalEepromResourceSystem(ExternalEeprom* eeprom, rbfs_t *rbfs);

protected:

    virtual int readBytes(unsigned int address, unsigned char* buf, int len);

    virtual void writeBytes(unsigned int address, unsigned char* buf, int len);
};

#endif	/* __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_H__ */

