//
// Created by Guillaume Tran on 05/02/2024.
//

#include "../../../include/components/elementary/NotComponent.hpp"

std::vector<Pin *> getNotComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::INPUT_PIN));
    list.push_back(new Pin(2, nts::OUTPUT_PIN));
    return list;
}

NotComponent::NotComponent(const std::string name) : AComponent(name, getNotComponentPins(), false)
{
    _truthTable = {
        {{nts::Tristate::True}, nts::Tristate::False},
        {{nts::Tristate::False}, nts::Tristate::True},
        {{nts::Tristate::Undefined}, nts::Tristate::Undefined}
    };
}

nts::Tristate NotComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return _next;
    if (_truthTable.empty())
        return nts::Tristate::Undefined;
    nts::Tristate val1 = conditionalComputePin(1);
    nts::Tristate newVal = _truthTable[{val1}];

    if (_next != newVal) {
        _next = newVal;
        conditionalComputePin(2);
    }
    return _next;
}
