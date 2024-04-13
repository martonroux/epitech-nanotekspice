//
// Created by Guillaume Tran on 05/02/2024.
//

#include "components/special/TrueComponent.hpp"
#include "Errors.hpp"
#include <iostream>

std::vector<Pin *> getTrueComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::OUTPUT_PIN));
    return list;
}

TrueComponent::TrueComponent(const std::string &name) : IOComponent(name, getTrueComponentPins())
{
    _curr = nts::True;
    _next = nts::True;
}

nts::Tristate TrueComponent::compute(std::size_t pin)
{
    if (pin == 1)
        return _curr;
    if (pin == (std::size_t)-1) {
        conditionalComputePin(1);
        return _curr;
    }
    return nts::Undefined;
}
