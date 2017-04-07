#pragma once
#include <cstdint>

#define FNV1_32_INIT ((uint32_t)0x811c9dc5)
uint32_t hash_str(const char *str, uint32_t hval = FNV1_32_INIT);
