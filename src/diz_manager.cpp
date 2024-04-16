#include "diz_manager.h"

DizPlatform::DizPlatform(const std::string &board, const std::string &engine, const std::string &version)
{
    this->board = board;
    this->engine = engine;
    this->version = version;
}

std::string DizPlatform::getBoard()
{
    return board;
}

std::string DizPlatform::getEngine()
{
    return engine;
}

std::string DizPlatform::getVersion()
{
    return version;
}

bool DizManager::readFile(const std::string &filename)
{
    this->filePath = filename;
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }
    std::string line = {};
    DizSection currentSection = {DizSection::NONE};

    int currentPlatform = {0};
    std::string currentPlatformBoard = {};
    std::string currentPlatformEngine = {};
    std::string currentPlatformVersion = {};
    while (getline(file, line))
    {
        if (DizManager::removeNewlines(line) == "[global]")
        {
            currentSection = DizSection::GLOBAL;
        }
        else if (DizManager::removeNewlines(line) == "[platform]")
        {
            currentSection = DizSection::PLATFORM;
            // skip bumping for the first found correct platform
            if (currentPlatformBoard != "" && currentPlatformEngine != "")
            {
                DizPlatform platform = DizPlatform(currentPlatformBoard, currentPlatformEngine, currentPlatformVersion);
                this->platforms.push_back(platform);
                currentPlatform++;
            }
        }
        else if (currentSection == DizSection::GLOBAL)
        {
            std::size_t found = line.find("appname=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("appname=").length();
                this->appName = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("appfile=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("appfile=").length();
                this->appFile = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("version=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("version=").length();
                this->version = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }
        }
        else if (currentSection == DizSection::PLATFORM)
        {
            std::size_t found = line.find("board=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("board=").length();
                currentPlatformBoard = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("engine=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("engine=").length();
                currentPlatformEngine = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("version=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("version=").length();
                currentPlatformVersion = DizManager::removeNewlines(line.substr(found + lastpos));
                continue;
            }
        }
    }
    // TODO separate function for this?
    if (currentPlatformBoard != "" && currentPlatformEngine != "")
    {
        DizPlatform platform = DizPlatform(currentPlatformBoard, currentPlatformEngine, currentPlatformVersion);
        this->platforms.push_back(platform);
        currentPlatform++;
    }

    file.close();
    return true;
}

constexpr std::string DizManager::removeNewlines(std::string s)
{
    std::size_t found = s.find('\r');
    if (found != std::string::npos)
    {
        s.erase(found, 1);
    }
    found = s.find('\n');
    if (found != std::string::npos)
    {
        s.erase(found, 1);
    }

    return s;
}

std::string DizManager::getAppName()
{
    return appName;
}

std::string DizManager::getAppFile()
{
    return appFile;
}

std::string DizManager::getVersion()
{
    return version;
}

std::vector<DizPlatform> DizManager::getPlatforms()
{
    return platforms;
}
