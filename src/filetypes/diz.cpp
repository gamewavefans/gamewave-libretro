#include "diz.h"

// TODO: use namespaces filetypes::diz::diz()
// TODO: move constructor?
DizPlatform::DizPlatform(const std::string &engine, const std::string &version)
{
    this->engine = engine;
    this->version = version;
}

std::string DizPlatform::getSafeEngine() const
{
    auto safeEngine = engine;
    if (safeEngine[0] == '/')
    {
        safeEngine.erase(0, 1);
    }
    return helpers::toLower(safeEngine);
}

std::string DizPlatform::getEngine() const
{
    return engine;
}

std::string DizPlatform::getVersion() const
{
    return version;
}

bool DIZ::readFile(const std::string &filePath)
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
        if (DIZ::removeNewlines(line) == "[global]")
        {
            currentSection = DizSection::GLOBAL;
        }
        else if (DIZ::removeNewlines(line) == "[platform]")
        {
            currentSection = DizSection::PLATFORM;
            // skip bumping for the first found correct platform
            if (currentPlatformBoard != "" && currentPlatformEngine != "")
            {
                DizPlatform platform = DizPlatform(currentPlatformEngine, currentPlatformVersion);
                this->platforms.insert({currentPlatformBoard, platform});
            }
        }
        else if (currentSection == DizSection::GLOBAL)
        {
            std::size_t found = line.find("appname=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("appname=").length();
                this->appName = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("appfile=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("appfile=").length();
                this->appFile = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("version=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("version=").length();
                this->version = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }
        }
        else if (currentSection == DizSection::PLATFORM)
        {
            std::size_t found = line.find("board=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("board=").length();
                currentPlatformBoard = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("engine=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("engine=").length();
                currentPlatformEngine = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }

            found = line.find("version=");
            if (found != std::string::npos)
            {
                constexpr int lastpos = std::string("version=").length();
                currentPlatformVersion = DIZ::removeNewlines(line.substr(found + lastpos));
                continue;
            }
        }
    }
    // TODO separate function for this?
    if (currentPlatformBoard != "" && currentPlatformEngine != "")
    {
        DizPlatform platform = DizPlatform(currentPlatformEngine, currentPlatformVersion);
        this->platforms.insert({currentPlatformBoard, platform});
    }

    file.close();
    return true;
}

constexpr std::string DIZ::removeNewlines(std::string s)
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

std::string DIZ::getAppName() const
{
    return appName;
}

std::string DIZ::getAppFile() const
{
    return appFile;
}

std::string DIZ::getSafeAppFile() const
{
    std::string safeAppFile = appFile;
    if (safeAppFile[0] == '/')
    {
        safeAppFile.erase(0, 1);
    }
    return helpers::toLower(safeAppFile);
}

std::string DIZ::getVersion() const
{
    return version;
}

std::map<std::string, DizPlatform> DIZ::getPlatforms() const
{
    return platforms;
}
