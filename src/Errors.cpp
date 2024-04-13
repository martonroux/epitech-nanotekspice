/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Errors.cpp
*/

#include "Errors.hpp"

const char* nts::Error::what() const noexcept
{
    return _msg.c_str();
}
