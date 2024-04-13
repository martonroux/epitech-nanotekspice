/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Enums.hpp
*/

#ifndef ENUMS_HPP
#define ENUMS_HPP

namespace nts
{
    enum PinType {
        INPUT_PIN,
        OUTPUT_PIN,
        NONE_PIN
    };
    enum Tristate {
        Undefined = (- true),
        True = true,
        False = false
    };
}

#endif
