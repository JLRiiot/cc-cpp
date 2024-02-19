#ifndef RUNME_UTILS_H
#define RUNME_UTILS_H

#include <vector>

typedef std::vector<unsigned char> byte_array;

void xor_blocks(const byte_array &b1, const byte_array &b2, byte_array &out);

#endif
