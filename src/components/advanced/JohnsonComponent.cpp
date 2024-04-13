/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** JohnsonComponent.cpp
*/

#include "components/advanced/JohnsonComponent.hpp"
#include <vector>

#include "Errors.hpp"

std::vector<Pin *> getJohsnonPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::OUTPUT_PIN));
    list.push_back(new Pin(2, nts::OUTPUT_PIN));
    list.push_back(new Pin(3, nts::OUTPUT_PIN));
    list.push_back(new Pin(4, nts::OUTPUT_PIN));
    list.push_back(new Pin(5, nts::OUTPUT_PIN));
    list.push_back(new Pin(6, nts::OUTPUT_PIN));
    list.push_back(new Pin(7, nts::OUTPUT_PIN));
    list.push_back(new Pin(9, nts::OUTPUT_PIN));
    list.push_back(new Pin(10, nts::OUTPUT_PIN));
    list.push_back(new Pin(11, nts::OUTPUT_PIN));
    list.push_back(new Pin(12, nts::OUTPUT_PIN));
    list.push_back(new Pin(13, nts::INPUT_PIN));
    list.push_back(new Pin(14, nts::INPUT_PIN));
    list.push_back(new Pin(15, nts::INPUT_PIN));
    return list;
}

JohnsonComponent::JohnsonComponent(std::string name) :
    AComponent(std::move(name), getJohsnonPins(), true)
{
    for (int i = 0; i < 10; i++)
        _outs.push_back(nts::Undefined);
}

void JohnsonComponent::simulate(__attribute__((unused))std::size_t tick)
{
    _cp0.first = _cp0.second;
    _cp1.first = _cp1.second;
    _mr.first = _mr.second;
}

nts::Tristate JohnsonComponent::compute(std::size_t pin)
{
    if ((*this)[pin]->getType() == nts::OUTPUT_PIN)
        return computeOutput(pin);
    return computeInput(pin);
}

nts::Tristate JohnsonComponent::computeOutput(std::size_t pin) const
{
    int idx = -1;

    if (pin == 1) idx = 5;
    if (pin == 2) idx = 1;
    if (pin == 3) idx = 0;
    if (pin == 4) idx = 2;
    if (pin == 5) idx = 6;
    if (pin == 6) idx = 7;
    if (pin == 7) idx = 3;
    if (pin == 9) idx = 8;
    if (pin == 10) idx = 4;
    if (pin == 11) idx = 9;
    if (pin == 12) idx = -2;

    if (idx == -1)
        throw nts::ComponentError("Johnson Component error. Should not happen. [JohnsonComponent.cpp > computeOutput()]");
    if (idx == -2)
        return _outB;
    return _outs[idx];
}

nts::Tristate JohnsonComponent::computeInput(std::size_t pin)
{
    bool changed = false;

    if (pin == 14) {     // CP0
        nts::Tristate val = conditionalComputePin(14);
        if (val != _cp0.second) {
            changed = true;
            _cp0.first = _cp0.second;
            _cp0.second = val;
        }
    }
    if (pin == 13) {     // CP1
        nts::Tristate val = conditionalComputePin(13);
        if (val != _cp1.second) {
            changed = true;
            _cp1.first = _cp1.second;
            _cp1.second = val;
        }
    }
    if (pin == 15) {     // MR
        nts::Tristate val = conditionalComputePin(15);
        if (val != _mr.second) {
            changed = true;
            _mr.first = _mr.second;
            _mr.second = val;
        }
    }

    if (changed) {
        pilot();
    }
    return nts::Undefined;
}

void JohnsonComponent::pilot()
{
    if (_mr.second == nts::True) {
        resetNumber();
        callOutputs();
        return;
    }
    if (_cp0.second == nts::False &&
        _cp0.first == nts::True &&
        _cp1.second == nts::False) {
        incrementNumber();
        callOutputs();
    }
}

void JohnsonComponent::incrementNumber()
{
    bool wasPrevious = false;

    for (int i = 0; i < 10; i++) {
        if (_outs[i] == nts::True) {
            _outs[i] = nts::False;
            wasPrevious = true;
            continue;
        }
        if (wasPrevious) {
            _outs[i] = nts::True;
            wasPrevious = false;
            if (i >= 5)
                _outB = nts::False;
            else
                _outB = nts::True;
        }
    }
    if (wasPrevious == true) {  // Was last digit
        resetNumber();
    }
}

void JohnsonComponent::resetNumber()
{
    _outs[0] = nts::True;

    for (int i = 1; i < 10; i++)
        _outs[i] = nts::False;
    _outB = nts::True;
}

void JohnsonComponent::callOutputs()
{
    for (Pin *pin : _pins) {
        if (pin->getType() == nts::OUTPUT_PIN) {
            pin->pinCompute();
        }
    }
}
