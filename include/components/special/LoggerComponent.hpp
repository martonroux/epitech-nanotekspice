/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** LoggerComponent.hpp
*/

#ifndef LOGGERCOMPONENT_HPP
#define LOGGERCOMPONENT_HPP

#include "components/AComponent.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

class LoggerComponent : public AComponent {
public:
    explicit LoggerComponent(std::string name);
    ~LoggerComponent() override = default;

    nts::Tristate compute(std::size_t pin) override;
    int8_t getPinValue();
    static void writeInLoggerFile(char c);
};



#endif //LOGGERCOMPONENT_HPP
