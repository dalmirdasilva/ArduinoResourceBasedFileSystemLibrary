/**
 * Arduino - A simple resource implementation
 * 
 * ResourceSystem.h
 * 
 * This is the Resource system itself.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_RESOURCE_SYSTEM_H__
#define __ARDUINO_SIMPLE_RESOURCE_SYSTEM_H__ 1

#include "ResourceSystem.h"
#include <Resource.h>
#include <srbfs.h>

#define RESOURCE_SYSTEM_CACHE_SIZE 32

class ResourceSystem {

    srbfs_t *srbfs;
    Resource::ResourceOperationResult lastOperationResult;

    bool wasCacheChanged, wasCacheInitialized;
    unsigned int cacheMemoryAddress;
    unsigned char cache[RESOURCE_SYSTEM_CACHE_SIZE];
    unsigned int cacheMiss, cacheHit;
    unsigned int validCacheSize;

public:

    enum MountOptions {
        MOUNT_READ_WRITE = 0,
        MOUNT_READ_ONLY = 1
    };

    ResourceSystem(srbfs_t *srbfs);

    Resource::ResourceOperationResult getLastOperationResult() {
        return lastOperationResult;
    }

    virtual bool format();

    virtual bool mount(MountOptions options);

    virtual bool umount();

    virtual Resource allocResource();

    virtual Resource loadResource(int code);

    virtual unsigned int totalSpace();

    virtual unsigned int availableSpace();

    virtual void flush();

protected:

    virtual int readBytes(unsigned int address, unsigned char* buf, int len) = 0;

    virtual void writeBytes(unsigned int address, unsigned char* buf, int len) = 0;

private:

    unsigned char read(unsigned char driver, unsigned int address);

    void write(unsigned char driver, unsigned int address, unsigned char b);

    void checkCache(uint16_t address);
};

#endif // __ARDUINO_SIMPLE_RESOURCE_SYSTEM_H__
