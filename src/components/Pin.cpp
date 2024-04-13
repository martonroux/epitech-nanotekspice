/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Pin.cpp
*/

#include "components/Pin.hpp"
#include "Errors.hpp"
#include "IComponent.hpp"
#include <iostream>

Pin::Pin(std::size_t pinNb, nts::PinType pinType) : _pinNb(pinNb), _pinType(pinType)
{
}

Pin::~Pin()
{
    for (ConnectionPair *pair : _comp) {
        delete pair;
    }
    _comp.clear();
}

void Pin::assign(std::size_t pinConnect, nts::IComponent& comp)
{
    if (comp[pinConnect]->getType() == _pinType)
        throw nts::PinConnectionError("Tried connecting two pins of same type.");
    if (_pinType == nts::OUTPUT_PIN) {
        _comp.push_back(new ConnectionPair(pinConnect, comp));
    } else {
        if (!_comp.empty())
            throw nts::PinConnectionError("Tried connecting multiple components to a single Input Pin.");
        _comp.push_back(new ConnectionPair(pinConnect, comp));
    }
}

nts::Tristate Pin::pinCompute()
{
    if (_comp.empty())
        return nts::Undefined;
    if (_pinType == nts::OUTPUT_PIN) {
        for (unsigned long i = 0; i < _comp.size(); i++) {
            _comp[i]->second.compute(_comp[i]->first);
        }
        return nts::Undefined;
    }
    nts::Tristate res = _comp[0]->second.compute(_comp[0]->first);
    return res;
}

nts::PinType Pin::getType() const
{
    return _pinType;
}

std::size_t Pin::getPinNb() const
{
    return _pinNb;
}
