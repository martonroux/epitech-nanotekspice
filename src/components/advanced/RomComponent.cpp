//
// Created by Guillaume Tran on 27/02/2024.
//

#include "components/advanced/RomComponent.hpp"

RomComponent::RomComponent(std::string name, std::vector<Pin *> pins) : AComponent(name, pins, false) {
    _memory.reserve(16384);
    for (std::size_t i = 0; i < 16384; i++) {
        _memory.push_back(nts::Tristate::Undefined);
    }
}

bool RomComponent::openBinaryFile() {
    std::ifstream file("rom.bin", std::ios::in | std::ios::binary);
    char buffer[16384];

    if (!file.is_open()) {
        return false;
    }
    file.read(buffer, 16384);
    for (std::size_t i = 0; i < 16384; i++) {

        if (buffer[i] < 0 || buffer[i] > 1) {
            _memory[i] = nts::Tristate::Undefined;
            continue;
        }
        _memory[i] = static_cast<nts::Tristate>(buffer[i]);
    }
    file.close();
    return true;
}

nts::Tristate RomComponent::compute(std::size_t pin) {
    if (pin == 20) {
        _read = conditionalComputePin(pin);
        for (int i = 9; i < 18; i++) {
            if (i == 12)
                continue;
            conditionalComputePin(i);
        }
    }

    if (pin == 18) {
        nts::Tristate res = conditionalComputePin(pin);
        if (res == nts::Tristate::Undefined) {
            return nts::Tristate::Undefined;
        }
        if (res == nts::Tristate::False) {
            return nts::Tristate::Undefined;
        }
        if (!openBinaryFile()) {
            return nts::Tristate::Undefined;
        }
        for (int i = 9; i < 18; i++) {
            if (i == 12)
                continue;
            conditionalComputePin(i);
        }
        return nts::Tristate::Undefined;
    }
    if (pin > 8 && pin < 18 && pin != 12) {
        int sum = 0;
        int n = 9;
        if (pin > 12) {
            n++;
        }
        sum = getSum();
        _next = _memory[sum + pin - n] == 0 ? nts::Tristate::False : nts::Tristate::True;
        if (_memory[sum + pin - n] < 0) {
            _next = nts::Tristate::Undefined;
        }

        return std::min(_next, _read);
    }
    if (pin <= 8 || pin == 23 || pin == 22 || pin == 19) {
        conditionalComputePin(pin);
    }
    return nts::Tristate::True;
}

int RomComponent::getSum() {
    int sum = 0;

    for (int i = 1; i < 9; i++) {
        sum += (*this)[i]->pinCompute() * (1 << (i - 1));
    }
    sum += (*this)[23]->pinCompute() * (1 << (23 - 1));
    sum += (*this)[22]->pinCompute() * (1 << (22 - 1));
    sum += (*this)[19]->pinCompute() * (1 << (19 - 1));
    return sum;
}