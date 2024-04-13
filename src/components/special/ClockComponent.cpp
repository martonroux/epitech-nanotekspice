//
// Created by Guillaume Tran on 07/02/2024.
//

#include "components/special/ClockComponent.hpp"

std::vector<Pin *> getClockComponentPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::OUTPUT_PIN));
    return list;
}

ClockComponent::ClockComponent(const std::string name) : InputComponent(name)
{
}

void ClockComponent::simulate(__attribute__((unused))std::size_t tick)
{
    conditionalComputePin(1);
    _curr = _next;

    if (_curr == nts::False)
        _next = nts::True;
    else if (_curr == nts::True)
        _next = nts::False;
}
