/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** FalseComponent.cpp
*/

#include "components/special/FalseComponent.hpp"
#include "Errors.hpp"
#include <iostream>

std::vector<Pin *> getFalseComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::OUTPUT_PIN));
    return list;
}

FalseComponent::FalseComponent(const std::string name) : IOComponent(name, getFalseComponentPins())
{
    _curr = nts::False;
    _next = nts::False;
}

nts::Tristate FalseComponent::compute(std::size_t pin)
{
    if (pin == 1)
        return _curr;
    if (pin == (std::size_t)-1) {
        conditionalComputePin(1);
        return _curr;
    }
    return nts::Undefined;
}
