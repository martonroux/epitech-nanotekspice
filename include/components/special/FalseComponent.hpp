/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** FalseComponent.hpp
*/

#ifndef FALSECOMPONENT_HPP
#define FALSECOMPONENT_HPP

#include "components/IOComponent.hpp"

class FalseComponent : public IOComponent {
public:
    explicit FalseComponent(const std::string name);
    ~FalseComponent() override = default;

    nts::Tristate compute(std::size_t pin) override;
};



#endif //FALSECOMPONENT_HPP
