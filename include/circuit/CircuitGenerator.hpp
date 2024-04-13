/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** CircuitGenerator.hpp
*/

#ifndef CIRCUITGENERATOR_HPP
#define CIRCUITGENERATOR_HPP

#include "parser/Parser.hpp"
#include "Circuit.hpp"

using PinConnection = std::pair<std::size_t, nts::IComponent&>;
using PinPair = std::pair<PinConnection, PinConnection>;

class CircuitGenerator {
private:
    Parser _parser;
    std::string _gateName;

    // STATIC
    static void assignPin(PinPair pair);
    static void createCircuitPin(Circuit *circuit, PinPair pair);

    // GETTERS
    Circuit *getGate();

    // SETTERS
    void addInputOutputs(Circuit *circuit);
    void addSims(Circuit *circuit);
    void generatePins(Circuit *circuit);
    void simulateConstPins(Circuit *circuit);

public:
    // CONTR DESTRUCT
    CircuitGenerator(Parser parser, std::string gateName);
    explicit CircuitGenerator(Parser parser);
    ~CircuitGenerator() = default;

    // RUNTIME
    Circuit *createGate();
    Circuit *createCircuit();
};



#endif //CIRCUITGENERATOR_HPP
