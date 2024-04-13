/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** OutputComponent.cpp
*/

#include "components/special/OutputComponent.hpp"
#include <iostream>

std::vector<Pin *> getOutputComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::INPUT_PIN));
    return list;
}

OutputComponent::OutputComponent(std::string name) : IOComponent(name, getOutputComponentPins())
{
}

nts::Tristate OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    _next = conditionalComputePin(1);
    return _next;
}
