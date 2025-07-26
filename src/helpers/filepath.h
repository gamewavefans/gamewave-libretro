#pragma once

#include <filesystem>
#include <iostream>

/**
 * @brief returns proper path on all systems, since Game Wave is case-insensitive
 * we usually expect absolute path, since we''l first have base path + resource dir
 * then additional (sub)directories and files.
 *
 * @param path case-insensitive path to the file we want
 * @return case-sensitive path on Unix-like systems, as-is on Windows
 */
std::string getPath(std::string path);
