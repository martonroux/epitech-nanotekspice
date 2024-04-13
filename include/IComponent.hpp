/*
** EPITECH PROJECT, 2024
** NanoTeckSpice
** File description:
** IComponent.hpp
*/

#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <cstddef>
#include "Enums.hpp"
#include "components/Pin.hpp"

namespace nts
{
    class IComponent
    {
    public:
        // DESTRUCT
        virtual ~IComponent() = default;

        // RUNTIME
        virtual void simulate(std::size_t tick) = 0;
        virtual Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, IComponent & other, std::size_t otherPin) = 0;

        // GETTERS
        virtual Pin *operator[](std::size_t pin) const = 0;
        virtual std::string getName() const = 0;
        virtual bool isSimulatable() const = 0;

        // SETTERS
        virtual void setName(const std::string& name) = 0;
    };
}

#endif
