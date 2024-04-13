/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** JohnsonComponent.hpp
*/

#ifndef JOHNSONCOMPONENT_HPP
#define JOHNSONCOMPONENT_HPP

#include "components/AComponent.hpp"

using StatePair = std::pair<nts::Tristate, nts::Tristate>;

class JohnsonComponent : public AComponent {
private:
    StatePair _cp0 = {nts::Undefined, nts::Undefined};
    StatePair _cp1 = {nts::Undefined, nts::Undefined};
    StatePair _mr = {nts::Undefined, nts::Undefined};
    std::vector<nts::Tristate> _outs;
    nts::Tristate _outB = nts::Undefined;

public:
    explicit JohnsonComponent(std::string name);
    ~JohnsonComponent() override = default;

    void simulate(std::size_t tick) override;

    nts::Tristate compute(std::size_t pin) override;
    nts::Tristate computeOutput(std::size_t pin) const;
    nts::Tristate computeInput(std::size_t pin);
    void pilot();
    void incrementNumber();
    void resetNumber();
    void callOutputs();
};



#endif //JOHNSONCOMPONENT_HPP
