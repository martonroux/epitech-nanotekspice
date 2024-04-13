/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Parser.cpp
*/

#include "parser/Parser.hpp"
#include <fstream>
#include "circuit/Circuit.hpp"
#include "circuit/CircuitGenerator.hpp"
#include "components/advanced/JohnsonComponent.hpp"
#include "components/elementary/AndComponent.hpp"
#include "components/elementary/OrComponent.hpp"
#include "components/elementary/XorComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/elementary/NotComponent.hpp"
#include "components/elementary/InhibitComponent.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/TrueComponent.hpp"
#include "components/special/ClockComponent.hpp"
#include "components/special/LoggerComponent.hpp"
#include "components/advanced/RomComponent.hpp"
#include "parser/ParseUtils.hpp"

Parser::Parser(std::string filename): _filename(filename) {
    factoryMap["xor"] = [](const std::string& name) {
        return new XorComponent(name);
    };
    factoryMap["or"] = [](const std::string& name) {
        return new OrComponent(name);
    };
    factoryMap["not"] = [](const std::string& name) {
        return new NotComponent(name);
    };
    factoryMap["and"] = [](const std::string& name) {
        return new AndComponent(name);
    };
    factoryMap["input"] = [](const std::string& name) {
        return new InputComponent(name);
    };
    factoryMap["output"] = [](const std::string& name) {
        return new OutputComponent(name);
    };
    factoryMap["true"] = [](const std::string& name) {
        return new TrueComponent(name);
    };
    factoryMap["false"] = [](const std::string& name) {
        return new FalseComponent(name);
    };
    factoryMap["circuit"] = [](const std::string& name) {
        return new Circuit(name);
    };
    factoryMap["clock"] = [](const std::string& name) {
        return new ClockComponent(name);
    };
    factoryMap["logger"] = [](const std::string& name) {
        return new LoggerComponent(name);
    };
    factoryMap["inhibit"] = [](const std::string& name) {
        return new InhibitComponent(name);
    };
    factoryMap["4017"] = [](const std::string& name) {
        return new JohnsonComponent(name);
    };
}

Parser::~Parser()
{
}

void Parser::parse() {
    std::string line;

    if (!fileExists(_filename))
        throw nts::FileNotFound("File [" + _filename + "] does not exist");
    if (!fileIsNTSFile(_filename))
        throw nts::InvalidFile("Invalid file with incorrect extension (awaited .nts): " + _filename);

    std::ifstream file(_filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            line = removeCommentsLine(line);
            if (line.empty())
                continue;
            convert_line(line);
        }
        file.close();
        if (_components.empty())
            throw nts::InvalidFile("Given file has no components.");
        return;
    }
    throw nts::InvalidFile("File could not be opened.");
}

void Parser::createGate(const std::string& name, const std::string& type, std::string gateFile)
{
    Parser gateParser(std::move(gateFile));

    gateParser.parse();
    CircuitGenerator generator(gateParser, type);
    _components[name] = generator.createGate();
    _components[name]->setName(name);
}

void Parser::addComponent(std::string type, std::string name)
{
    if (componentExists(name))
        throw nts::ComponentNameDuplicate("Component duplicate found in nts file: {type: [" + type + "], name: [" + name + "]}");
    if (factoryMap.find(type) != factoryMap.end()) {
        _components[name] = factoryMap[type](name);
        if (type == "input" || type == "clock")
            _inputs.push_back(_components[name]);
        if (type == "output")
            _outputs.push_back(_components[name]);
    } else {
        std::string gateFile = findGateFile(type, "./circuits");

        if (!gateFile.empty()) {
            createGate(name, type, gateFile);
        } else {
            throw nts::InvalidComponent("Parser found an invalid component: {type: [" + type + "], name: [" + name + "]}.");
        }
    }
}

void Parser::addLink(std::string name1, std::size_t pin,
                     std::string name2, std::size_t pin2)
{
    if (!componentExists(name1))
        throw nts::ComponentNotFound("Component with name [" + name1 + "] wasn't found in list of components.");
    if (!componentExists(name2))
        throw nts::ComponentNotFound("Component with name [" + name2 + "] wasn't found in list of components.");
    _links.push_back({{pin, *_components[name1]}, {pin2, *_components[name2]}});
}

std::map<std::string, nts::IComponent*> Parser::components() const
{
    return _components;
}

std::vector<nts::IComponent*> Parser::inputs() const
{
    return _inputs;
}

std::vector<nts::IComponent*> Parser::outputs() const
{
    return _outputs;
}

std::vector<PinPair> Parser::links() const
{
    return _links;
}

bool Parser::componentExists(std::string name) const
{
    for (std::pair<std::string, nts::IComponent*> comp : _components) {
        if (comp.first == name)
            return true;
    }
    return false;
}

Parser::State Parser::getState(const std::string& line) const
{
    if (line == ".chipsets:") {
        return CHIPSET;
    }
    if (line == ".links:") {
        if (_current_state != CHIPSET)
            throw nts::InvalidFile("Found .links part of nts file before .chipsets");
        return LINKS;
    }
    return _current_state;
}

void Parser::convert_line(std::string line) {
    _current_state = getState(line);

    if (_current_state == CHIPSET && line.find('.') == std::string::npos){
        std::pair<std::string, std::string> comp = convertComponent(line);
        addComponent(comp.first, comp.second);
    } else if (_current_state == LINKS && line.find('.') == std::string::npos) {
        LinkPair pair = convertLink(line);
        addLink(pair.first.first, pair.first.second, pair.second.first, pair.second.second);
    }
}

LinkPair Parser::convertLink(std::string line)
{
    Link link1;
    Link link2;

    std::replace( line.begin(), line.end(), '\t', ' ');
    std::string part1 = line.substr(0, line.find(' '));
    std::string part2 = line.substr(part1.length(), line.length());

    part1 = removeSpaces(part1);
    part2 = removeSpaces(part2);

    parseLinkPart(part1, line, link1);
    parseLinkPart(part2, line, link2);
    return {link1, link2};
}

std::pair<std::string, std::string> Parser::convertComponent(std::string line)
{
    std::replace( line.begin(), line.end(), '\t', ' ');
    std::string part1 = line.substr(0, line.find(' '));
    std::string part2 = line.substr(part1.length(), line.length());

    part1 = removeSpaces(part1);
    part2 = removeSpaces(part2);

    if (part2.empty())
        throw nts::InvalidComponent("Incorrect nts file at line: [" + line + "]");
    return {part1, part2};
}
