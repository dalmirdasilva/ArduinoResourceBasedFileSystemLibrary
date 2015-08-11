/**
 * Arduino - A simple resource implementation
 * 
 * ResourceSystem.cpp
 * 
 * This is the Resource system itself.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_RESOURCE_SYSTEM_CPP__
#define __ARDUINO_SIMPLE_RESOURCE_SYSTEM_CPP__ 1

#include "ResourceSystem.h"

ResourceSystem::ResourceSystem(srbfs_t *srbfs)
        : srbfs(srbfs) {
    lastOperationResult = Resource::OPERATION_SUCCESS;
    srbfs->io->read = &read;
    srbfs->io->write = &write;
}

bool ResourceSystem::format() {
    Resource::ResourceOperationResult o = (Resource::ResourceOperationResult) srbfs_format(srbfs);
    return (o == Resource::OPERATION_SUCCESS);
}

bool ResourceSystem::mount(MountOptions options) {
    lastOperationResult = (Resource::ResourceOperationResult) srbfs_mount(srbfs, (srbfs_mount_options_t) options);
    return (lastOperationResult == Resource::OPERATION_SUCCESS);
}

void ResourceSystem::flush() {
    if (wasCacheChanged) {
        writeBytes(cacheMemoryAddress, cache, validCacheSize);
    }
}

bool ResourceSystem::umount() {
    flush();
    lastOperationResult = (Resource::ResourceOperationResult) srbfs_umount(srbfs);
    return (lastOperationResult == Resource::OPERATION_SUCCESS);
}

Resource ResourceSystem::allocResource() {
    flush();
    Resource rw(RS_NULL_RESOURCE_CODE, srbfs);
    srbfs_resource_code_t code;
    code = srbfs_alloc(srbfs);
    if (code != RS_NULL_RESOURCE_CODE) {
        rw.setCode(code);
    }
    return rw;
}

Resource ResourceSystem::loadResource(int code) {
    flush();
    Resource resource((srbfs_resource_code_t) code, srbfs);
    resource.srbfs = srbfs;
    resource.code = code;
    return resource;
}

unsigned int ResourceSystem::totalSpace() {
    return (unsigned int) srbfs_total_space(srbfs);
}

unsigned int ResourceSystem::availableSpace() {
    return (unsigned int) srbfs_available_space(srbfs);
}


unsigned char ResourceSystem::read(unsigned char driver, unsigned int address) {
    checkCache(address);
    if (validCacheSize < 1) {
        lastOperationResult = Resource::OPERATION_ERROR_IO_ERROR;
        return 0;
    }
    return (uint8_t) cache[address - cacheMemoryAddress];
}

void ResourceSystem::write(unsigned char driver, unsigned int address, unsigned char b) {
    checkCache(address);
    cache[address - cacheMemoryAddress] = b;
    wasCacheChanged = true;
}

void ResourceSystem::checkCache(uint16_t address) {
    if (!wasCacheInitialized || (address < cacheMemoryAddress || address >= (cacheMemoryAddress + validCacheSize))) {
        flush();
        validCacheSize = readBytes(address, cache, RESOURCE_SYSTEM_CACHE_SIZE);
        cacheMemoryAddress = address;
        wasCacheChanged = false;
        wasCacheInitialized = true;
        cacheMiss++;
    } else {
        cacheHit++;
    }
}

#endif /* __ARDUINO_SIMPLE_RESOURCE_SYSTEM_CPP__ */
