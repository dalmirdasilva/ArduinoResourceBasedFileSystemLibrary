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

ResourceSystem::ResourceSystem(rbfs_t *rbfs)
        : rbfs(rbfs) {
    lastOperationResult = Resource::OPERATION_SUCCESS;
}

bool ResourceSystem::format() {
    Resource::ResourceOperationResult o = (Resource::ResourceOperationResult) rbfs_format(rbfs);
    return (o == Resource::OPERATION_SUCCESS);
}

bool ResourceSystem::mount(MountOptions options) {
    lastOperationResult = (Resource::ResourceOperationResult) rbfs_mount(rbfs->driver, rbfs, (rbfs_mount_options_t) options);
    return (lastOperationResult == Resource::OPERATION_SUCCESS);
}

void ResourceSystem::flush() {
    if (wasCacheChanged) {
        writeBytes(cacheMemoryAddress, cache, validCacheSize);
    }
}

bool ResourceSystem::umount() {
    flush();
    lastOperationResult = (Resource::ResourceOperationResult) rbfs_umount(rbfs);
    return (lastOperationResult == Resource::OPERATION_SUCCESS);
}

Resource ResourceSystem::allocResource() {
    flush();
    Resource resource(RBFS_NULL_RESOURCE_CODE, rbfs);
    rbfs_resource_code_t code;
    code = rbfs_alloc(rbfs);
    if (code != RBFS_NULL_RESOURCE_CODE) {
        resource.setCode(code);
    }
    return resource;
}

Resource ResourceSystem::loadResource(int code) {
    flush();
    Resource resource((rbfs_resource_code_t) code, rbfs);
    resource.setRbfs(rbfs);
    resource.setCode(code);
    return resource;
}

unsigned int ResourceSystem::totalSpace() {
    return (unsigned int) rbfs_total_space(rbfs);
}

unsigned int ResourceSystem::availableSpace() {
    return (unsigned int) rbfs_available_space(rbfs);
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
