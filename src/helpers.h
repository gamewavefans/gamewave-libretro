#pragma once

#include <cstdint>
#include <string>
#include <algorithm>

namespace helpers
{
    // TODO: move it elsewhere
    unsigned int packPixel(uint8_t r, uint8_t g, uint8_t b);

    std::string toLower(std::string s);
}
