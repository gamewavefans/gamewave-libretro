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
    auto buffer = new char[size];
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
    // memcpy(header, buffer, 4);
    std::copy(buffer, buffer + 4, header.data());
    return header == packedHeader;
}

std::pair<char *, uint> ZBC::decompress(char *buffer)
{
    uint32_t uncompressedSize = {0};
    uint32_t compressedSize = {0};
    memcpy(&uncompressedSize, buffer + 0x8, sizeof(compressedSize));
    memcpy(&compressedSize, buffer + 0xC, sizeof(compressedSize));

    auto compressedData = new char[compressedSize];
    auto uncompressedData = new char[uncompressedSize];

    memcpy(compressedData, buffer + 0x10, compressedSize);

    // TODO: move zlib to a helper function, this will be used in many places
    z_stream strm = {};
    strm.avail_in = compressedSize;
    strm.avail_out = uncompressedSize;
    strm.next_in = (Bytef *)compressedData;
    strm.next_out = (Bytef *)uncompressedData;

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
