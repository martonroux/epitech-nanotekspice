/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** OutputComponent.hpp
*/

#ifndef OUTPUTCOMPONENT_HPP
#define OUTPUTCOMPONENT_HPP

#include "components/IOComponent.hpp"

class OutputComponent : public IOComponent {
public:
    explicit OutputComponent(std::string name);
    ~OutputComponent() override = default;

    nts::Tristate compute(std::size_t pin) override;
};



#endif //OUTPUTCOMPONENT_HPP
