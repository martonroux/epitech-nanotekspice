/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** IoComponent.cpp
*/

#include "components/IOComponent.hpp"

IOComponent::IOComponent(std::string name, std::vector<Pin*> pins) : AComponent(name, pins, true)
{
}

nts::Tristate IOComponent::getCurrent()
{
    return _curr;
}
