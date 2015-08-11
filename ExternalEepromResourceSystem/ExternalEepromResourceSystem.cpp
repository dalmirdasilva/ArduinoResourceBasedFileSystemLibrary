/**
 * Arduino - A simple resource implementation
 * 
 * SimpleExternalEepromResourceIO.cpp
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_CPP__
#define __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_CPP__ 1

#include "ExternalEepromResourceSystem.h"
#include <ResourceSystem.h>

ExternalEepromResourceSystem::ExternalEepromResourceSystem(ExternalEeprom* eeprom, rbfs_t *rbfs) : ResourceSystem(rbfs), eeprom(eeprom) {
}

int ExternalEepromResourceSystem::readBytes(unsigned int address, unsigned char* buf, int len) {
    return eeprom->readBytes(address, buf, len);
}

void ExternalEepromResourceSystem::writeBytes(unsigned int address, unsigned char* buf, int len) {
    eeprom->writeBytes(address, buf, len);
}

#endif	/* __ARDUINO_SIMPLE_EXTERNAL_EEPROM_RESOURCE_IO_CPP__ */

