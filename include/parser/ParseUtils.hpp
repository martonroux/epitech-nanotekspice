//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef PARSEUTILS_HPP
#define PARSEUTILS_HPP

#include <string>
#include "Errors.hpp"
#include <filesystem>

#include "IComponent.hpp"

using Link = std::pair<std::string, int>;

bool fileExists(const std::string& filename);
std::string removeCommentsLine(std::string line);
std::string removeSpaces(std::string line);
Link parseLinkPart(std::string part, std::string line, Link& link);
bool fileIsNTSFile(std::string filename);
std::string filenameRemoveExtension(const std::string& filename, const std::string& folderPath);
std::string findGateFile(const std::string& name, const std::string& folderPath);



#endif //PARSEUTILS_HPP
