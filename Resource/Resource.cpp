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

Resource::Resource(rbfs_resource_code_t code, rbfs_t* rbfs) : code(code), rbfs(rbfs) {
    lastOperationResult = OPERATION_SUCCESS;
}

bool Resource::open(OpenOptions options) {
    lastOperationResult = (ResourceOperationResult) rbfs_open(rbfs, code, &resource, (rbfs_open_resource_options_t) options);
    return (lastOperationResult == OPERATION_SUCCESS);
}

bool Resource::close() {
    sync();
    lastOperationResult = (ResourceOperationResult) rbfs_close(rbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::write(unsigned char b) {
    lastOperationResult = (ResourceOperationResult) rbfs_write(rbfs, &resource, b);
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
    return rbfs_read(rbfs, &resource);
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
    lastOperationResult = (ResourceOperationResult) rbfs_seek(rbfs, &resource, (rbfs_seek_origin_t) origin, (rbfs_seek_int_t) offset);
    return (lastOperationResult == OPERATION_SUCCESS);
}

bool Resource::truncate() {
    lastOperationResult = (ResourceOperationResult) rbfs_truncate(rbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::sync() {
    rbfs_sync(rbfs, &resource);
    // TODO: flush();
}

bool Resource::rewind() {
    lastOperationResult = (ResourceOperationResult) rbfs_rewind(rbfs, &resource);
    return (lastOperationResult == OPERATION_SUCCESS);
}

void Resource::release() {
    sync();
    rbfs_release(rbfs, &resource);
}

unsigned int Resource::size() {
    return (unsigned int) rbfs_size(&resource);
}

unsigned int Resource::tell() {
    return (unsigned int) rbfs_tell(&resource);
}

bool Resource::eor() {
    return (rbfs_eor(&resource) != 0);
}

bool Resource::error() {
    return (rbfs_error(&resource) != 0);
}

bool Resource::isReadOnly() {
    return (rbfs->flags & RBFS_RESOURCE_FLAG_BIT_READ_ONLY) != 0;
}

#endif /* __ARDUINO_SIMPLE_RESOURCE_CPP__ */
