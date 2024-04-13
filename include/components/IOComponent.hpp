/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** IoComponent.hpp
*/

#ifndef IOCOMPONENT_HPP
#define IOCOMPONENT_HPP

#include "components/AComponent.hpp"
#include <vector>

class IOComponent : public AComponent {
public:
    IOComponent(std::string name, std::vector<Pin *> pins);
    ~IOComponent() override = default;

    nts::Tristate getCurrent();
};



#endif //IOCOMPONENT_HPP
