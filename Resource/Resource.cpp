/**
 * Arduino - A simple resource implementation
 * 
 * Resource.cpp
 * 
 * This is the Resource representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_RESOURCE_CPP__
#define __ARDUINO_SIMPLE_RESOURCE_CPP__ 1

#include "Resource.h"

Resource::Resource(srbfs_resource_code_t code, srbfs_t* srbfs) : code(code), srbfs(srbfs) {
    lastOperationResult = OPERATION_SUCCESS;
}

bool Resource::open(OpenOptions options) {
    lastOperationResult = (ResourceOperationResult) srbfs_open(srbfs, code, &resource, (srbfs_open_resource_options_t) options);
    return (lastOperationResult == OPERATION_SUCCESS);
}

bool Resource::close() {
    sync();
    lastOperationResult = (ResourceOperationResult) srbfs_close(srbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::write(unsigned char b) {
    lastOperationResult = (ResourceOperationResult) srbfs_write(srbfs, &resource, b);
}

void Resource::writeBytes(unsigned char* buf, int count) {
    lastOperationResult = OPERATION_SUCCESS;
    for (int i = 0; i < count && lastOperationResult == OPERATION_SUCCESS; i++) {
        write(buf[i]);
    }
}

int Resource::read() {
    if (eor()) {
        return -1;
    }
    return srbfs_read(srbfs, &resource);
}

int Resource::readBytes(unsigned char* buf, int count) {
    int i, c;
    if (buf == (unsigned char*) 0) {
        return 0;
    }
    c = read();
    if (c == -1) {
        return -1;
    }
    buf[0] = c;
    for (i = 1; i < count; i++) {
        c = read();
        if (c == -1) {
            break;
        }
        buf[i] = c;
    }
    return i;
}

bool Resource::seek(ResourceSeekOrigin origin, unsigned int offset) {
    lastOperationResult = (ResourceOperationResult) srbfs_seek(srbfs, &resource, (srbfs_seek_origin_t) origin, (srbfs_seek_int_t) offset);
    return (lastOperationResult == OPERATION_SUCCESS);
}

bool Resource::truncate() {
    lastOperationResult = (ResourceOperationResult) srbfs_truncate(srbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::sync() {
    srbfs_sync(srbfs, &resource);
    ResourceIO::getAssociatedIO(srbfs->driver)->flush();
}

bool Resource::rewind() {
    lastOperationResult = (ResourceOperationResult) srbfs_rewind(srbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::release() {
    sync();
    srbfs_release(srbfs, &resource);
}

unsigned int Resource::size() {
    return (unsigned int) srbfs_size(&resource);
}

unsigned int Resource::tell() {
    return (unsigned int) srbfs_tell(&resource);
}

bool Resource::eor() {
    return (srbfs_eor(&resource) != 0);
}

bool Resource::error() {
    return (srbfs_error(&resource) != 0);
}

bool Resource::isReadOnly() {
    return (srbfs->flags & RS_RESOURCE_FLAG_BIT_READ_ONLY) != 0;
}

#endif /* __ARDUINO_SIMPLE_RESOURCE_CPP__ */
