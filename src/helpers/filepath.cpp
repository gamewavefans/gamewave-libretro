#include "helpers/filepath.h"

std::string getPath(std::string path)
{
#ifdef _WIN32
    // on Windows just return path as-is, it should handle the path as case-insensitive anyway
    // we convert "/" to "\" anyway, to have nice path handling on Windows
    std::filesystem::path p = path;
    p.make_preferred();
    return p.string();
#else
    // only work with UNIX-like paths, in case some game uses "\\"
    std::replace(path.begin(), path.end(), '\\', '/');
    std::filesystem::path p = path;
    auto components = std::distance(p.begin(), p.end());
    // TODO: what if path is empty? throw here? return as-is? This onyl happ[ens when path is empty I think
    if (components < 1)
    {
        return path;
    }

    std::filesystem::path newPath = *(p.begin());

    for (auto it = ++p.begin(); it != p.end(); ++it)
    {
        std::string itLower = (*it).string();
        std::transform(itLower.begin(), itLower.end(), itLower.begin(), ::tolower);

        // TODO: this conversion will break on UTF-8 paths, but that'd require ICU library
        // This shouldn't be a problem, since tha base path sould always be in proper case, and the rest provided by game will always be in ASCII
        bool foundElement = {false};

        if (std::filesystem::is_directory(newPath))
        {
            for (const auto &entry : std::filesystem::directory_iterator(newPath))
            {
                std::string elementLower = entry.path().filename();
                std::transform(elementLower.begin(), elementLower.end(), elementLower.begin(), ::tolower);
                if (elementLower == itLower)
                {
                    foundElement = true;
                    newPath /= entry.path().filename();
                    break;
                }
            }
            if (!foundElement)
            {
                // TODO: use throw instead of cerr?
                std::cerr << std::format("Could not find element {} in path {}", itLower, newPath.string()) << std::endl;
                return "";
            }
        }
        else
        {
            auto newPathComponents = std::distance(newPath.begin(), newPath.end());
            if (components != newPathComponents)
            {
                std::cerr << std::format("Expected {} elements, got {}", components, newPathComponents) << std::endl;
                return "";
            }
        }
    }
    return newPath.string();
#endif
}
