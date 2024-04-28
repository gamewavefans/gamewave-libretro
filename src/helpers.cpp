#include "helpers.h"

// TODO: move it elsewhere
unsigned int packPixel(uint8_t r, uint8_t g, uint8_t b)
{
    return (static_cast<int>(r) << 16) + (static_cast<int>(g) << 8) + static_cast<int>(b);
}
