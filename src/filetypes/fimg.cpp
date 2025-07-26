#include "fimg.h"

/*
typedef struct {
    char name[40];
    int address <format=hex>;
    int size;

    local int currentPosition = FTell();
    FSeek(baseAddr + address);
    char data[size];
    FSeek(currentPosition);
} FileHeader <read=Str("%s, 0x%x, 0x%x",this.name, this.address, this.size)>;
*/

// TODO: split this ugly function
// try nto to mix buffer and then seeking in the file again
FIMG::FIMG(fs::path &filename)
{
    // load engine file
    std::ifstream engine{filename, std::ios::binary | std::ios::ate};
    auto size = engine.tellg();
    engine.seekg(0, std::ios::beg);
    std::vector<char> buffer(size, 0);
    engine.read(buffer.data(), size);
    std::vector<unsigned char> test{buffer.begin(), buffer.end()};

    // find magic in the file
    auto magicPos = std::search(test.begin(), test.end(), magic.begin(), magic.end());
    if (magicPos == test.end())
    {
        throw std::runtime_error("FIMG magic not found in the file");
    }

    // read files
    auto baseFimgPos = std::distance(test.begin(), magicPos);
    engine.seekg(baseFimgPos + 8, std::ios::beg);
    uint32_t filesCount = helpers::readBigEndianInt(engine);

    for (uint32_t i = 0; i < filesCount; i++)
    {
        char name[40]{};
        engine.read(name, 40);
        auto address = helpers::readBigEndianInt(engine);
        auto size = helpers::readBigEndianInt(engine);

        auto currentPos = engine.tellg();

        engine.seekg(baseFimgPos + address, std::ios::beg);

        std::vector<char> data(size, 0);
        engine.read(data.data(), size);

        engine.seekg(currentPos, std::ios::beg);

        files.insert({name, data});
        log_cb(RETRO_LOG_DEBUG, "FIMG: found file %2.d/%d named \"%s\"\n", i + 1, filesCount, name);
    }
};

std::vector<char> FIMG::getFile(std::string &filename)
{
    return files.at(filename);
}

std::vector<char> FIMG::getFile(std::string filename)
{
    return files.at(filename);
}
