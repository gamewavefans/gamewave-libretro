#include "zbc.h"

ZBC::ZBC(std::string filename)
{
    std::ifstream f(filename, std::ifstream::in | std::ifstream::binary);
    if (!f.is_open())
    {
        throw std::runtime_error(std::format("file {} not found", filename));
    }
    f.seekg(0, std::ios::end);
    size = f.tellg();
    auto *buffer = new char[size];
    f.seekg(0);
    f.read(buffer, size);
    f.close();

    // TODO: check if file have a correct header, ZCS or ZBC
    // if(!hasCorrectHeader()) {
    //     throw std:runtime_error("incorrect header");
    // }

    if (isCompressed(buffer))
    {
        std::tie(data, size) = decompress(buffer);
        return;
    }

    data = buffer;
}

std::pair<char *, uint> ZBC::getUncompressed() const
{
    return std::make_pair(data, size);
}

bool ZBC::isCompressed(char *buffer)
{
    std::array<char, 4> packedHeader{'\x1b', 'Z', 'C', 'S'};
    std::array<char, 4> header = {};
    std::copy(buffer, buffer + 4, header.data());
    return header == packedHeader;
}

std::pair<char *, uint> ZBC::decompress(char *buffer)
{
    uint32_t uncompressedSize = {0};
    uint32_t compressedSize = {0};
    std::copy(buffer + 0x8, buffer + 0xC, reinterpret_cast<char *>(&uncompressedSize));
    std::copy(buffer + 0xC, buffer + 0x10, reinterpret_cast<char *>(&compressedSize));

    return helpers::zlibInflate(buffer + 0x10, compressedSize, uncompressedSize);
}
