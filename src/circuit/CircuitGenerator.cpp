/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** CircuitGenerator.cpp
*/

#include "circuit/CircuitGenerator.hpp"
#include "Errors.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/special/TrueComponent.hpp"

CircuitGenerator::CircuitGenerator(Parser parser, std::string gateName) : _parser(parser), _gateName(gateName)
{
}

CircuitGenerator::CircuitGenerator(Parser parser) : _parser(parser)
{
}

Circuit* CircuitGenerator::getGate()
{
    for (std::pair<std::string, nts::IComponent *> pair : _parser.components()) {
        if (pair.first == _gateName) {
            return dynamic_cast<Circuit *>(pair.second);
        }
    }
    return nullptr;
}

void CircuitGenerator::assignPin(PinPair pair)
{
    PinConnection comp1Connection = pair.first;
    PinConnection comp2Connection = pair.second;

    std::size_t comp1Pin = comp1Connection.first;
    nts::IComponent& component1 = comp1Connection.second;

    std::size_t comp2Pin = comp2Connection.first;
    nts::IComponent& component2 = comp2Connection.second;

    component2[comp2Pin]->assign(comp1Pin, component1);
    component1[comp1Pin]->assign(comp2Pin, component2);
}

void CircuitGenerator::createCircuitPin(Circuit *circuit, PinPair pair)
{
    PinConnection componentConnection = pair.first;
    PinConnection circuitConnection = pair.second;

    std::size_t compPin = componentConnection.first;
    std::size_t circuitPin = circuitConnection.first;

    nts::IComponent& comp = componentConnection.second;

    Pin *pinIn;
    Pin *pinOut;
    if (comp[compPin]->getType() == nts::INPUT_PIN) {
        pinIn = new Pin(circuitPin, nts::INPUT_PIN);
        pinOut = new Pin(-circuitPin, nts::OUTPUT_PIN);
    } else {
        pinIn = new Pin(-circuitPin, nts::INPUT_PIN);
        pinOut = new Pin(circuitPin, nts::OUTPUT_PIN);
    }
    if (circuit->addPin(pinIn) == false) // Already exists
        delete pinIn;
    if (circuit->addPin(pinOut) == false) // Already exists
        delete pinOut;
    pair.second.first = -circuitPin;
    assignPin(pair);
}

void CircuitGenerator::addInputOutputs(Circuit* circuit)
{
    for (nts::IComponent* input : _parser.inputs())
        circuit->addInput(input);

    for (nts::IComponent* output : _parser.outputs())
        circuit->addOutput(output);
}

void CircuitGenerator::addSims(Circuit* circuit)
{
    for (std::pair<std::string, nts::IComponent*> pair : _parser.components()) {
        nts::IComponent* comp = pair.second;

        if (comp == circuit)
            continue;
        if (comp->isSimulatable())
            circuit->addSims(comp);
    }
}

void CircuitGenerator::generatePins(Circuit* circuit)
{
    for (PinPair pair : _parser.links()) {
        if (pair.second.second.getName() == _gateName) {
            createCircuitPin(circuit, pair);
        } else if (pair.first.second.getName() == _gateName) {
            PinPair tempPair = {pair.second, pair.first};
            createCircuitPin(circuit, tempPair);
        } else {
            assignPin(pair);
        }
    }
}

void CircuitGenerator::simulateConstPins(Circuit *circuit)
{
    for (std::pair<std::string, nts::IComponent*> pair : _parser.components()) {
        if (typeid(*pair.second) == typeid(TrueComponent) ||
            typeid(*pair.second) == typeid(FalseComponent)) {
            pair.second->compute(-1);
            circuit->simulate(0);
        }
    }
}

Circuit* CircuitGenerator::createGate()
{
    if (_gateName.empty())
        throw nts::CircuitGeneratorError("gateName was not initialized in CircuitGenerator constructor, but createGate was called.");
    Circuit *circuit = getGate();

    if (circuit == nullptr)
        throw nts::CircuitGeneratorError("Did not find given gate [" + _gateName + "] in parser data.");
    generatePins(circuit);
    addInputOutputs(circuit);
    addSims(circuit);
    simulateConstPins(circuit);
    return circuit;
}

Circuit* CircuitGenerator::createCircuit()
{
    auto *circuit = new Circuit("main_circuit");

    for (PinPair pair : _parser.links())
        assignPin(pair);
    addInputOutputs(circuit);
    addSims(circuit);
    simulateConstPins(circuit);
    return circuit;
}
