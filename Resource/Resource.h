/**
 * Arduino - A simple resource implementation
 * 
 * SimpleResource.h
 * 
 * This is the Resource representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_RESOURCE_H__
#define __ARDUINO_SIMPLE_RESOURCE_H__ 1

#include <rbfs.h>

class Resource {

public:

    enum ResourceOperationResult {
        OPERATION_SUCCESS = 0,
        OPERATION_ERROR_RESOURCE_OPENED = 1,
        OPERATION_ERROR_RESOURCE_CLOSED = 2,
        OPERATION_ERROR_RESOURCE_READ_ONLY = 3,
        OPERATION_ERROR_NO_SPACE_AVAILABLE = 4,
        OPERATION_ERROR_DRIVER_BUSY = 5,
        OPERATION_ERROR_SEEK_OUT_OF_BOUND = 6,
        OPERATION_ERROR_RESOURCE_DOES_NOT_ALLOCATED = 7,
        OPERATION_ERROR_DRIVER_NOT_MOUNTED = 8,
        OPERATION_ERROR_IO_ERROR = 9
    };

    enum OpenOptions {
        OPEN_READ_WRITE = 0,
        OPEN_READ_ONLY = 1
    };

    enum ResourceSeekOrigin {
        SEEK_ORIGIN_BEGIN = 0,
        SEEK_ORIGIN_CURRENT = 1
    };

private:

    rbfs_resource_code_t code;
    rbfs_resource_t resource;
    rbfs_t* rbfs;
    ResourceOperationResult lastOperationResult;

public:

    Resource(rbfs_resource_code_t code, rbfs_t* rbfs);

    ResourceOperationResult getLastOperationResult() {
        return lastOperationResult;
    }

    void setCode(int code) {
        this->code = (rbfs_resource_code_t) code;
    }

    int getCode() {
        return (int) this->code;
    }

    void setRbfs(rbfs_t* rbfs) {
        this->rbfs = rbfs;
    }

    rbfs_t* getRbfs() {
        return this->rbfs;
    }

    bool open(OpenOptions options);

    bool close();

    void write(unsigned char b);

    void writeBytes(unsigned char* buf, int len);

    int read();

    int readBytes(unsigned char* buf, int len);

    bool seek(ResourceSeekOrigin origin, unsigned int offset);

    bool truncate();

    void sync();

    bool rewind();

    void release();

    unsigned int size();

    unsigned int tell();

    bool eor();

    bool error();

    bool isReadOnly();
};

#endif // __ARDUINO_SIMPLE_RESOURCE_H__
