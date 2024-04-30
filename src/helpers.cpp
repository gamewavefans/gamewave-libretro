#include "helpers.h"

namespace helpers
{
    // TODO: move it elsewhere
    unsigned int packPixel(uint8_t r, uint8_t g, uint8_t b)
    {
        return (static_cast<int>(r) << 16) + (static_cast<int>(g) << 8) + static_cast<int>(b);
    }

    std::string toLower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return s;
    }
}
