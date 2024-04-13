//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef NANOTEKSPICE_TRUECOMPONENT_HPP
#define NANOTEKSPICE_TRUECOMPONENT_HPP

#include "components/IOComponent.hpp"
#include <string>

class TrueComponent : public IOComponent {
public:
    // CONSTR DESTRUCT
    explicit TrueComponent(const std::string &name);
    ~TrueComponent() override = default;

    // FUNCS
    nts::Tristate compute(std::size_t pin) override;
};

#endif //NANOTEKSPICE_TRUECOMPONENT_HPP
