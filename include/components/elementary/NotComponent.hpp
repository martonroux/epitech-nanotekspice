//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef NOTCOMPONENT_HPP
#define NOTCOMPONENT_HPP

#include "../AComponent.hpp"
#include <map>

class NotComponent : public AComponent {
public:
    explicit NotComponent(std::string name);
    ~NotComponent() override = default;
    nts::Tristate compute(std::size_t pin) override;

private:
    std::map<std::tuple<nts::Tristate>, nts::Tristate> _truthTable = {};
};



#endif //NOTCOMPONENT_HPP
