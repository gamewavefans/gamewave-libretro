#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "deps/libretro-common/include/libretro.h"

enum class DizSection
{
    NONE,
    GLOBAL,
    PLATFORM
};
class DizPlatform
{
public:
    DizPlatform(const std::string board, const std::string engine, const std::string version);
    std::string getBoard();
    std::string getEngine();
    std::string getVersion();

private:
    std::string board;
    std::string engine;
    std::string version;
};

class DizManager
{
public:
    bool readFile(const std::string filename);

    std::string getAppName();
    std::string getAppFile();
    std::string getVersion();
    std::vector<DizPlatform> getPlatforms();

private:
    static constexpr std::string removeNewlines(std::string s);
    std::string filePath = {};
    std::string appName = {};
    std::string appFile = {};
    std::string version = {};
    std::vector<DizPlatform> platforms{};
};
