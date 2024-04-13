//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

#include "components/AComponent.hpp"
#include <map>

class LogicComponent : public AComponent {
public:
    explicit LogicComponent(std::string nameIn);
    ~LogicComponent()override = default;
    nts::Tristate compute(std::size_t pin) override;

protected:
    std::map<std::tuple<nts::Tristate, nts::Tristate>, nts::Tristate> _truthTable = {};
};



#endif //LOGICCOMPONENT_H
