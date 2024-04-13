/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Circuit.hpp
*/

#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <map>
#include <vector>
#include "components/AComponent.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"

class Circuit : public AComponent {
private:
    std::vector<IComponent *> _inputs;
    std::vector<IComponent *> _outputs;
    std::vector<IComponent *> _sims;

public:
    // CONSTR DESTRUCT
    explicit Circuit(std::string name);
    ~Circuit() override;

    // RUNTIME
    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;
    void displayOutputs();
    void displayInputs();
    void displayDebug(std::string namesBefore);
    bool setInput(std::string name, nts::Tristate state);

    // SETTERS
    bool addPin(Pin* pin);
    void addInput(IComponent* input);
    void addOutput(IComponent* output);
    void addSims(IComponent* sims);

    // OPERATORS
};



#endif //CIRCUIT_HPP
