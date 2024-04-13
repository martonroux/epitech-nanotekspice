//
// Created by Guillaume Tran on 05/02/2024.
//

#include "parser/ParseUtils.hpp"

bool fileExists(const std::string& filename)
{
    if (filename.empty())
        return false;
    return true;
}

std::string removeCommentsLine(std::string line) {
    if (line.find('#') != std::string::npos) {
        line = line.erase(line.find('#'), line.length());
    }
    while (line[0] == ' ' || line[0] == '\t') {
        line.erase(0, 1);
    }
    return line;
}

std::string removeSpaces(std::string line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == ' ') {
            line.erase(i, 1);
            i --;
        }
    }
    return line;
}

Link parseLinkPart(std::string part, std::string line, Link& link) {
    size_t colonPos = part.find(':');

    if (colonPos == std::string::npos || colonPos == 0 || colonPos == part.length() - 1)
        throw nts::InvalidFile("Invalid nts file at line: [" + line + "]");
    std::string strPart = part.substr(0, colonPos);
    std::string intPart = part.substr(colonPos + 1);
    try {
        link.first = strPart;
        link.second = std::stoi(intPart);
    } catch (const std::exception&) {
        throw nts::InvalidFile("Invalid nts file at line: [" + line + "]");
    }
    return link;
}

bool fileIsNTSFile(std::string filename)
{
    std::string extension = filename.substr(filename.length() - 4, 4);

    if (extension == ".nts")
        return true;
    return false;
}

std::string filenameRemoveExtension(const std::string& filename, const std::string& folderPath)
{
    std::string newStr = filename;

    newStr.erase(newStr.length() - 4, 4);
    newStr.erase(0, folderPath.length());
    if (newStr[0] == '/')
        newStr.erase(0, 1);
    return newStr;
}

std::string findGateFile(const std::string& name, const std::string& folderPath)
{
    for (const auto & entry : std::filesystem::directory_iterator(folderPath)) {
        std::string file = entry.path();

        if (!fileIsNTSFile(file))
            continue;
        std::string thisName = filenameRemoveExtension(file, folderPath);
        if (thisName == name)
            return file;
    }
    return "";
}
