/**
 * Arduino - A simple resource implementation
 * 
 * SimpleArrayResourceIO.h
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_H__
#define __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_H__ 1

#include <ResourceSystem.h>
#include <rbfs.h>

class ArrayResourceSystem : public ResourceSystem {

private:
    unsigned char* array;
    unsigned int size;

public:

    ArrayResourceSystem(unsigned char* array, unsigned int size, rbfs_t *rbfs);

protected:
    
    virtual int readBytes(unsigned int address, unsigned char* buf, unsigned int len);

    virtual void writeBytes(unsigned int address, unsigned char* buf, unsigned int len);
};

#endif	/* __ARDUINO_SIMPLE_ARRAY_RESOURCE_IO_H__ */

