//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef ORCOMPONENT_HPP
#define ORCOMPONENT_HPP

#include "LogicComponent.hpp"


class OrComponent : public LogicComponent {
public:
    explicit OrComponent(std::string name);
    ~OrComponent() override = default;
};



#endif //ORCOMPONENT_HPP
