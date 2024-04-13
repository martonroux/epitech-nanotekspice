/*
** EPITECH PROJECT, 2024
** NanoTeckSpice
** File description:
** AComponent.hpp
*/

#ifndef ACOMPONENT_HPP
#define ACOMPONENT_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <exception>
#include "IComponent.hpp"

class AComponent : public nts::IComponent {
protected:
    std::string _name;
    bool _simulatable;
    std::vector<Pin *> _pins;

    nts::Tristate _curr = nts::Undefined;
    nts::Tristate _next = nts::Undefined;

    // CONSTR
    AComponent(std::string name, std::vector<Pin *> pins, bool simulatable);

public:
    // DESTRUCT
    ~AComponent() override;

    // RUNTIME
    // Virtual
    nts::Tristate compute(std::size_t pin) override = 0;

    // Implemented
    void simulate(std::size_t tick) override;
    void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override;
    nts::Tristate conditionalComputePin(std::size_t pin) const;

    // OPERATOR
    Pin *operator[](std::size_t pin) const override;

    // GETTERS
    std::string getName() const override;
    bool isSimulatable() const override;

    // SETTERS
    void setName(const std::string& name) override;
};



#endif //ACOMPONENT_HPP
