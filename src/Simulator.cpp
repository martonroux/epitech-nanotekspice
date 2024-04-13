/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Simulator.cpp
*/
//
// Created by Guillaume Tran on 06/02/2024.
//

#include "Simulator.hpp"
#include <csignal>

Simulator::Simulator(std::string filename) {
    _commands = {
            {"exit", [this]() -> int {
                return exitSim();
            }},
            {"display", [this]() -> int {
                display();
                return 0;
            }},
            {"simulate", [this]() -> int {
                simulate();
                return 0;
            }},
            {"loop", [this]() -> int {
                loop();
                return 0;
            }},
            {"debug", [this]() -> int {
                debug();
                return 0;
            }},
    };

    _parser = new Parser(filename);
    _parser->parse();
    CircuitGenerator generator(*_parser, "xor");
    _circuit = generator.createCircuit();
}

Simulator::~Simulator() {
    delete _parser;
    delete _circuit;
}

int Simulator::display() {
    std::cout << "tick: " << _tick << std::endl;
    std::cout << "input(s):" << std::endl;
    _circuit->displayInputs();
    std::cout << "output(s):" << std::endl;
    _circuit->displayOutputs();
    return 0;
}

int Simulator::exitSim() {
    return 1;
}

int Simulator::simulate() {
    _tick++;
    _circuit->simulate(_tick);
    return 0;
}

volatile sig_atomic_t isRunning = 1;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        isRunning = 0;
    }
}

int Simulator::loop() {
    std::signal(SIGINT, signal_handler);

    while (isRunning) {
        simulate();
        display();
    }
    isRunning = 1;
    return 0;
}

int Simulator::debug()
{
    _circuit->displayDebug("");
    return 0;
}

void Simulator::checkAssignation(std::string command)
{
    std::string name = command.substr(0, command.find('='));
    std::string value = command.substr(command.find('=') + 1);
    nts::Tristate triValue;

    if (value == "0")
        triValue = nts::False;
    else if (value == "1")
        triValue = nts::True;
    else if (value == "U")
        triValue = nts::Undefined;
    else
        throw nts::InvalidAssignement("Invalid value for input: " + value);

    bool found = _circuit->setInput(name, triValue);

    if (!found)
        throw nts::InvalidAssignement("Tried to assign value to input [" + name + "], but this input doesn't exist.");
}

int Simulator::run() {
    std::string command;
    int res = 0;

    while (std::cout << "> " && std::getline(std::cin, command)) {
        if (command.empty()) {
            continue;
        }
        try {
            if (_commands.find(command) != _commands.end()) {
               res = _commands[command]();
               if (res == 1) {
                   return 1;
               }
            } else if (command.find('=') != std::string::npos) {
                checkAssignation(command);
            } else {
                throw nts::CommandNotFound("Command [" + command + "] wasn't found in list of available commands.");
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
