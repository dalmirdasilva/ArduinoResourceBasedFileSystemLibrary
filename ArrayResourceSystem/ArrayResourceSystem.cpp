/**
 * Arduino - A simple resource implementation
 * 
 * SimpleArrayResourceIO.cpp
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_CPP__
#define __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_CPP__ 1

#include "ArrayResourceSystem.h"

ArrayResourceSystem::ArrayResourceSystem(unsigned char* array, unsigned int size, rbfs_t *rbfs) : ResourceSystem(rbfs), array(array), size(size) {
}

int ArrayResourceSystem::readBytes(unsigned int address, unsigned char* buf, unsigned int len) {
    unsigned int available = (size - address);
    if (available < 1) {
        return -1;
    }
    len = (len > available) ? available : len;
    for (unsigned int i = 0; i < len; i++) {
        buf[i] = array[address + i];
    }
    return len;
}

void ArrayResourceSystem::writeBytes(unsigned int address, unsigned char* buf, unsigned int len) {
    for (unsigned int i = 0; i < len && (address + i) < size; i++) {
        array[address + i] = buf[i];
    }
}

#endif	/* __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_CPP__ */

