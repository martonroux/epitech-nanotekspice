/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** InputComponent.hpp
*/

#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include "components/IOComponent.hpp"

class InputComponent : public IOComponent {
public:
    explicit InputComponent(std::string name);
    ~InputComponent() override = default;

    nts::Tristate compute(std::size_t pin) override;
    void setNextValue(nts::Tristate value);
};



#endif //INPUTCOMPONENT_HPP
