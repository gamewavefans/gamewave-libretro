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

    std::pair<char *, uint> zlibInflate(char *compressedData, uint compressedSize, uint uncompressedSize)
    {
        auto *uncompressedData = new char[uncompressedSize];

        // TODO: move zlib to a helper function, this will be used in many places
        z_stream strm = {};
        strm.avail_in = compressedSize;
        strm.avail_out = uncompressedSize;
        strm.next_in = reinterpret_cast<Bytef *>(compressedData);
        strm.next_out = reinterpret_cast<Bytef *>(uncompressedData);

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;

        int err = -1;

        err = inflateInit2(&strm, 15);
        if (err != Z_OK)
        {
            inflateEnd(&strm);
            throw std::runtime_error("inflateInit2 failed");
        }

        err = inflate(&strm, Z_FINISH);
        if (err != Z_STREAM_END)
        {
            inflateEnd(&strm);
            throw std::runtime_error(std::format("inflate failed: {} {}", err, strm.total_in));
        }
        inflateEnd(&strm);

        if (uncompressedSize != strm.total_out)
        {
            throw std::runtime_error("uncompressed size mismatch");
        }

        return std::make_pair(uncompressedData, uncompressedSize);
    }
}
