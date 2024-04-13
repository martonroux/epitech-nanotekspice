//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>
#include "IComponent.hpp"
#include "Errors.hpp"
#include <iostream>

// _links = [ {{pin, component}, {pin, component}} ]

using PinConnection = std::pair<std::size_t, nts::IComponent&>;
using PinPair = std::pair<PinConnection, PinConnection>;
using Link = std::pair<std::string, int>;
using LinkPair = std::pair<Link, Link>;

class Parser {
public:
    enum State {
        CHIPSET,
        LINKS,
        NONE
    };
    // CONSTR DESTRUCT
    explicit Parser(std::string filename);
    ~Parser();

    // RUNTIME
    void parse();
    void convert_line(std::string line);
    static LinkPair convertLink(std::string line);
    static std::pair<std::string, std::string> convertComponent(std::string line);
    void createGate(const std::string& name, const std::string& type, std::string gateFile);

    // SETTERS
    void addComponent(std::string type, std::string name);
    void addLink(std::string name1, std::size_t pin, std::string name2, std::size_t pin2);

    // GETTERS
    std::map<std::string, nts::IComponent*> components() const;
    std::vector<nts::IComponent*> inputs() const;
    std::vector<nts::IComponent*> outputs() const;
    std::vector<PinPair> links() const;
    State getState(const std::string& line) const;

private:
    std::string _filename;
    State _current_state = NONE;
    std::map<std::string, nts::IComponent *> _components;
    std::vector<nts::IComponent*> _inputs;
    std::vector<nts::IComponent*> _outputs;
    std::vector<PinPair> _links;
    std::map<std::string, std::function <nts::IComponent*(const std::string&)>> factoryMap;

    bool componentExists(std::string name) const;
};

#endif //PARSER_HPP
