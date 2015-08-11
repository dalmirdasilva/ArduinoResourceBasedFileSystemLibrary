/**
 * Arduino - A simple resource implementation
 * 
 * VirtualResourceSystem.cpp
 * 
 * This is the Resource IO representation.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_CPP__
#define __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_CPP__ 1

#include <stdio.h>
#include <stddef.h>
#include "VirtualResourceSystem.h"

VirtualResourceSystem::VirtualResourceSystem(srbfs_t *srbfs, char *fileName) : ResourceSystem(srbfs), fileName(fileName) {
    open();
}

bool VirtualResourceSystem::open() {
    fp = fopen(fileName, "rb+");
    if (fp == NULL) {
        printf("Error when opening file: %s.\n", fileName);
        exit(1);
    }
    return true;
}

void VirtualResourceSystem::flush() {
    SimpleResourceIO::flush();
    fflush(fp);
}

void VirtualResourceSystem::close() {
    SimpleResourceIO::close();
    fclose(fp);
}

int VirtualResourceSystem::readBytes(unsigned int address, unsigned char* buf, int len) {
    fseek(fp, address, 0);
    return (int) fread(buf, sizeof(unsigned char), len, fp);
}

void VirtualResourceSystem::writeBytes(unsigned int address, unsigned char* buf, int len) {
    fseek(fp, address, 0);
    fwrite(buf, sizeof(unsigned char), len, fp);
}

#endif	/* __ARDUINO_SIMPLE_VIRTUAL_RESOURCE_IO_CPP__ */

