#pragma once

#include <utility>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>
#include <vector>
#include <map>

#include "global.h"
#include "helpers.h"

namespace fs = std::filesystem;

class FIMG
{
public:
    FIMG(fs::path &engineFile);

    std::vector<char> getFile(std::string &filename);
    std::vector<char> getFile(std::string filename);

private:
    // FIMG starts with bytes 0x 12 34 56 78 87 65 43 21 in big endian
    std::array<unsigned char, 8> magic = {0x12, 0x34, 0x56, 0x78, 0x87, 0x65, 0x43, 0x21};
    std::map<std::string, std::vector<char>> files;
};
