#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "helpers.h"

/** DizSection is a helper enum for parsing Diz files,
 * we store info about the currently processed section of the file
 */
enum class DizSection
{
    NONE,
    GLOBAL,
    PLATFORM
};

/** DizPlatform stores information about a platform from a .diz file
 *
 */
class DizPlatform
{
public:
    /** Stores information about a platform from a .diz file
     */
    DizPlatform(const std::string &board, const std::string &engine, const std::string &version);
    std::string getBoard() const;
    std::string getEngine() const;
    std::string getVersion() const;

private:
    std::string board;
    std::string engine;
    std::string version;
};

// TODO: shouldn't this be DizLoader to keep one naming convention?
// TODO: throw exception instead of this wonky readFile function
/**DizManager loads Diz file and stores its values inside
 */
class DizManager
{
public:
    /**
     * @brief readFile reads .diz file and stores its values
     *
     * @param filePath path to a .diz file
     * @return Returns true if a file was read succesfully
     */
    bool readFile(const std::string &filePath);

    /** retrieves appname field
     */
    std::string getAppName() const;

    /** retrieves appfile field, containing path to a .zbc file
     */
    std::string getAppFile() const;

    /**
     * @brief retrieves lowercase appFile field, without leading slash
     * @return lowercase appFile field, without leading slash
     */
    std::string getSafeAppFile() const;

    /** retrieves version field, if it exists
     */
    std::string getVersion() const;

    /** returns vector of platforms
     */
    std::vector<DizPlatform> getPlatforms() const;

private:
    static constexpr std::string removeNewlines(std::string s);
    std::string filePath = {};
    std::string appName = {};
    std::string appFile = {};
    std::string version = {};
    std::vector<DizPlatform> platforms{};
};
