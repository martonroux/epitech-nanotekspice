/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Pin.hpp
*/

#ifndef PIN_HPP
#define PIN_HPP

#include <cstddef>
#include <vector>
#include <utility>
#include "Enums.hpp"

// Forward declaration to avoid circular import
namespace nts {
    class IComponent;
}

using ConnectionPair = std::pair<std::size_t, nts::IComponent&>;

class Pin {
protected:
    std::size_t _pinNb = 0;
    nts::PinType _pinType;
    std::vector<ConnectionPair *> _comp;

public:
    Pin(std::size_t pinNb, nts::PinType pinType);
    virtual ~Pin();

    virtual void assign(std::size_t pinConnect, nts::IComponent& comp);
    nts::Tristate pinCompute();

    nts::PinType getType() const;
    std::size_t getPinNb() const;
};



#endif //PIN_HPP
