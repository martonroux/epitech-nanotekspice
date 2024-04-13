//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef B_OOP_400_MPL_4_1_TEKSPICE_MARTON_ROUX_ANDCOMPONENT_HPP
#define B_OOP_400_MPL_4_1_TEKSPICE_MARTON_ROUX_ANDCOMPONENT_HPP

#include "LogicComponent.hpp"

class AndComponent : public LogicComponent {
public:
    explicit AndComponent(std::string name);
    ~AndComponent() override = default;
};


#endif //B_OOP_400_MPL_4_1_TEKSPICE_MARTON_ROUX_ANDCOMPONENT_HPP
