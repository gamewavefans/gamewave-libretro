#pragma once

#include <iostream>
#include <fstream>
#include <vector>

// DizSection is a helper enum for parsing Diz files,
// we store info about the currently processed section of the file
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

/**DizManager loads Diz file and stores its values inside
 */
class DizManager
{
public:
    bool readFile(const std::string filename);

    /** retrieves appname field
     */
    std::string getAppName();

    /** retrieves appfile field, containing path to a .zbc file
     */
    std::string getAppFile();

    /** retrieves version field, if it exists
     */
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
