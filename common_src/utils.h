#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <byteswap.h>

uint32_t to_little_endian32(uint32_t buff);

uint16_t to_little_endian16(uint16_t buff);

#endif