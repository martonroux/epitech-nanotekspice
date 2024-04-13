//
// Created by Guillaume Tran on 07/02/2024.
//

#ifndef NANOTEKSPICE_CLOCKCOMPONENT_HPP
#define NANOTEKSPICE_CLOCKCOMPONENT_HPP

#include "components/AComponent.hpp"
#include "components/special/InputComponent.hpp"


class ClockComponent : public InputComponent {
public:
    explicit ClockComponent(std::string name);
    ~ClockComponent() override = default;

    void simulate(std::size_t tick) override;
};


#endif //NANOTEKSPICE_CLOCKCOMPONENT_HPP
