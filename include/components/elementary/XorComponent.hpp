//
// Created by Guillaume Tran on 05/02/2024.
//

#ifndef XORCOMPONENT_HPP
#define XORCOMPONENT_HPP

#include "LogicComponent.hpp"


class XorComponent : public LogicComponent {
public:
    explicit XorComponent(std::string name);
    ~XorComponent() override = default;
};



#endif //XORCOMPONENT_HPP
