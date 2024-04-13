/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Circuit.cpp
*/

#include "circuit/Circuit.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include "components/special/ClockComponent.hpp"
#include "Errors.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/special/TrueComponent.hpp"

Circuit::Circuit(std::string name) : AComponent(name, {}, true)
{
}

Circuit::~Circuit()
{
    for (IComponent *comp : _sims) {
        delete comp;
    }
    _sims.clear();
    _inputs.clear();
    _outputs.clear();
}

void Circuit::simulate(std::size_t tick)
{
    for (IComponent* sims : _sims) {
        sims->simulate(tick);
    }
}

nts::Tristate Circuit::compute(std::size_t pin)
{
    return (*this)[-pin]->pinCompute();
}

void Circuit::displayOutputs()
{
    nts::Tristate ret;
    std::vector<std::string> list;
    std::string string;

    for (IComponent* out : _outputs) {
        auto* comp = dynamic_cast<OutputComponent *>(out);
        ret = comp->getCurrent();
        string = "  " + comp->getName() + ": ";

        if (ret == nts::Undefined)
            string += "U";
        else if (ret == nts::False)
            string += "0";
        else
            string += "1";

        list.push_back(string);
    }
    std::sort(list.begin(), list.end());

    for (const std::string& toPrint : list)
        std::cout << toPrint << std::endl;
    list.clear();
}

void Circuit::displayInputs()
{
    nts::Tristate ret;
    std::vector<std::string> list;
    std::string string;

    for (IComponent* in : _inputs) {
        auto* comp = dynamic_cast<IOComponent *>(in);
        ret = comp->getCurrent();
        string = "  " + comp->getName() + ": ";

        if (ret == nts::Undefined)
            string += "U";
        else if (ret == nts::False)
            string += "0";
        else
            string += "1";

        list.push_back(string);
    }
    std::sort(list.begin(), list.end());

    for (const std::string& toPrint : list)
        std::cout << toPrint << std::endl;
    list.clear();
}

void Circuit::displayDebug(std::string namesBefore)
{
    std::vector<std::pair<std::size_t, nts::Tristate>> values;

    for (Pin *pin : _pins) {
        if (pin->getPinNb() < 1000 && pin->getType() == nts::INPUT_PIN) {
            values.push_back({pin->getPinNb(), pin->pinCompute()});
        }
    }
    std::cout << "Values for " << namesBefore + " > " + _name << ":" << std::endl;

    for (std::pair<std::size_t, nts::Tristate> val : values) {
        std::cout << "\t" << val.first << " " << val.second << std::endl;
    }

    for (IComponent* cmp : _sims) {
        if (typeid(*cmp) == typeid(Circuit)) {
            dynamic_cast<Circuit *>(cmp)->displayDebug(namesBefore + " > " + _name);
        }
    }
}

bool Circuit::setInput(std::string name, nts::Tristate state)
{
    for (IComponent *in : _inputs) {
        if (typeid(*in) == typeid(Circuit)) {
            bool ret = dynamic_cast<Circuit*>(in)->setInput(name, state);

            if (ret)
                return true;
        }
        if (in->getName() == name) {
            if (typeid(*in) != typeid(InputComponent) && typeid(*in) != typeid(ClockComponent))
                return false;
            dynamic_cast<InputComponent*>(in)->setNextValue(state);
            return true;
        }
    }
    return false;
}

bool Circuit::addPin(Pin* pin)
{
    try {
        (void)(*this)[pin->getPinNb()];
        return false;
    } catch (const nts::ComponentError& _) {
        _pins.push_back(pin);
        return true;
    }
}

void Circuit::addInput(IComponent* input)
{
    _inputs.push_back(input);
}

void Circuit::addOutput(IComponent* output)
{
    _outputs.push_back(output);
}

void Circuit::addSims(IComponent* sims)
{
    _sims.push_back(sims);
}
