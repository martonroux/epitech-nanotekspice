//
// Created by Guillaume Tran on 27/02/2024.
//

#ifndef NANOTEKSPICE_ROMCOMPONENT_HPP
#define NANOTEKSPICE_ROMCOMPONENT_HPP

#include "../AComponent.hpp"
#include <vector>
#include <fstream>
#include <iostream>

class RomComponent : public AComponent {
public:
    RomComponent(std::string name, std::vector<Pin *> pins);
    nts::Tristate compute(std::size_t pin) override;
    bool openBinaryFile();
    int getSum();
private:
    std::vector<nts::Tristate> _memory;
    nts::Tristate _read = nts::Tristate::Undefined;
};


#endif //NANOTEKSPICE_ROMCOMPONENT_HPP
