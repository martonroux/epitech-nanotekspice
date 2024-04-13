//
// Created by Guillaume Tran on 05/02/2024.
//

#include "components/elementary/LogicComponent.hpp"
#include <iostream>

std::vector<Pin *> getLogicComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::INPUT_PIN));
    list.push_back(new Pin(2, nts::INPUT_PIN));
    list.push_back(new Pin(3, nts::OUTPUT_PIN));
    return list;
}

LogicComponent::LogicComponent(std::string nameIn) :
    AComponent(nameIn, getLogicComponentPins(), true)
{
}

nts::Tristate LogicComponent::compute(std::size_t pin)
{
    if (pin == 3)
        return _next;
    if (_truthTable.empty())
        return nts::Undefined;
    nts::Tristate val1 = conditionalComputePin(1);
    nts::Tristate val2 = conditionalComputePin(2);

    nts::Tristate newVal = _truthTable[{val1, val2}];

    if (newVal != _next) {
        _next = newVal;
        conditionalComputePin(3);
    }
    return _next;
}
