#include "diz_manager.h"

DizPlatform::DizPlatform(const std::string &board, const std::string &engine, const std::string &version)
{
    this->board = board;
    this->engine = engine;
    this->version = version;
}

std::string DizPlatform::getBoard() const
{
    return board;
}

std::string DizPlatform::getEngine() const
{
    return engine;
}

std::string DizPlatform::getVersion() const
{
    return version;
}

bool DizManager::readFile(const std::string &filePath)
{
    this->filePath = filePath;
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }
    std::string line = {};
    DizSection currentSection = {DizSection::NONE};

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

std::string DizManager::getAppName() const
{
    return appName;
}

std::string DizManager::getAppFile() const
{
    return appFile;
}

std::string DizManager::getSafeAppFile() const
{
    std::string safeAppFile = appFile;
    if (safeAppFile[0] == '/')
    {
        safeAppFile.erase(0, 1);
    }
    return helpers::toLower(safeAppFile);
}

std::string DizManager::getVersion() const
{
    return version;
}

std::vector<DizPlatform> DizManager::getPlatforms() const
{
    return platforms;
}
