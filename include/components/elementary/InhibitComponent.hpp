//
// Created by Guillaume Tran on 01/03/2024.
//

#ifndef NANOTEKSPICE_INHIBITCOMPONENT_HPP
#define NANOTEKSPICE_INHIBITCOMPONENT_HPP

#include "LogicComponent.hpp"

class InhibitComponent : public LogicComponent {
public :
    explicit InhibitComponent(std::string name);
    ~InhibitComponent() override = default;
};


#endif //NANOTEKSPICE_INHIBITCOMPONENT_HPP
