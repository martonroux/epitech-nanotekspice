/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** InputComponent.cpp
*/

#include "components/special/InputComponent.hpp"
#include <iostream>

std::vector<Pin *> getInputComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::OUTPUT_PIN));
    return list;
}

InputComponent::InputComponent(std::string name) : IOComponent(std::move(name), getInputComponentPins())
{
}

nts::Tristate InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return _next;
}

void InputComponent::setNextValue(nts::Tristate value)
{
    if (value != _next) {
        _next = value;
        conditionalComputePin(1);
    } else {
        _next = value;
    }
}
