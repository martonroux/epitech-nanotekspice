/*
** EPITECH PROJECT, 2024
** NanoTeckSpice
** File description:
** AComponent.cpp
*/

#include "components/AComponent.hpp"

#include "Errors.hpp"

void AComponent::simulate(__attribute__((unused))std::size_t tick)
{
    _curr = _next;
}

void AComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if ((*this)[pin]->getType() == nts::OUTPUT_PIN)
        throw nts::PinConnectionError("Tried connecting two incompatible pins. ONLY compatible order: OUTPUT -> INPUT");
    if (other[otherPin]->getType() == nts::INPUT_PIN)
        throw nts::PinConnectionError("Tried connecting two incompatible pins. ONLY compatible order: OUTPUT -> INPUT");
    (*this)[pin]->assign(otherPin, other);
}

nts::Tristate AComponent::conditionalComputePin(std::size_t pin) const
{
    try {
        return (*this)[pin]->pinCompute();
    } catch (const nts::ComponentError& _) {
        return nts::Undefined;
    }
}

Pin *AComponent::operator[](std::size_t pin) const
{
    for (Pin *this_pin : _pins) {
        if (this_pin->getPinNb() == pin)
            return this_pin;
    }
    throw nts::ComponentError("Pin nb°" + std::to_string(pin) + " on component [" + _name + "] was not found.");
}

std::string AComponent::getName() const
{
    return _name;
}

bool AComponent::isSimulatable() const
{
    return true;
}

void AComponent::setName(const std::string& name)
{
    _name = name;
}

AComponent::AComponent(std::string name, std::vector<Pin *> pins, bool simulatable) :
    _name(std::move(name)), _simulatable(simulatable), _pins(pins)
{
}

AComponent::~AComponent()
{
    for (Pin* pin : _pins)
        delete pin;
    _pins.clear();
}
