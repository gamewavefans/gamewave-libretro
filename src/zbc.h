#pragma once

#include <utility>
#include <string>
#include <array>
#include <fstream>
#include <stdexcept>

#include <cstring>

#include <zlib.h>

#include "src/helpers.h"

// TODO: this can be done way better, for nw this is a quick and dirty implementation, a bare minimum to get the core working
// TODO: error handling
class ZBC
{
public:
    ZBC(std::string filename);
    std::pair<char *, uint> getUncompressed() const;
    // std::pair<char *, uint> getCompressed();

    // static std::vector<std::byte> compress(std::vector<std::byte>);

private:
    bool isCompressed(char *buffer);
    std::pair<char *, uint> decompress(char *data);
    // std::pair<char *, uint> compressBytecode();

    // for now we're only keeping uncompressed data in here, compressed is calculated on the fly
    char *data;
    uint size;
};
