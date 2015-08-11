/**
 * Arduino - A simple resource implementation
 * 
 * SimpleVirtualResourceIO.h
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_H__
#define __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_H__ 1

#include <stdio.h>
#include <ResourceSystem.h>

class VirtualResourceSystem : public ResourceSystem {
private:
    char *fileName;
    FILE *fp;
public:

    VirtualResourceSystem(srbfs_t* srbfs, char *fileName);

    virtual bool open();

    virtual void flush();
    
    virtual void close();

protected:
    
    virtual int readBytes(unsigned int address, unsigned char* buf, int len);

    virtual void writeBytes(unsigned int address, unsigned char* buf, int len);
};

#endif	/* __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_H__ */

