#pragma once

#include <utility>
#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <format>

#include <zlib.h>

namespace helpers
{
    // TODO: move it elsewhere
    unsigned int packPixel(uint8_t r, uint8_t g, uint8_t b);

    std::string toLower(std::string s);

    std::pair<char *, uint> zlibInflate(char *compressedData, uint compressedSize, uint uncompressedSize);
}
