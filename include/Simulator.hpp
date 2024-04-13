//
// Created by Guillaume Tran on 06/02/2024.
//

#ifndef NANOTEKSPICE_Simulator_HPP
#define NANOTEKSPICE_Simulator_HPP

#include <string>
#include <map>
#include <functional>
#include "parser/Parser.hpp"
#include "circuit/Circuit.hpp"
#include "circuit/CircuitGenerator.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "IComponent.hpp"

class Simulator {
public:
    explicit Simulator(std::string filename);
    ~Simulator();
    int exitSim();
    int display();
    int simulate();
    int loop();
    int debug();
    int run();
    void checkAssignation(std::string command);
private:
    std::map<std::string, std::function<int()>> _commands;
    Circuit *_circuit;
    Parser *_parser;
    int _tick = 0;
};


#endif //NANOTEKSPICE_Simulator_HPP
