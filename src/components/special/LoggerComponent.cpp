/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** LoggerComponent.cpp
*/

#include "components/special/LoggerComponent.hpp"

#include "Errors.hpp"

std::vector<Pin *> getLoggerPins()
{
    std::vector<Pin *> list;

    list.push_back(new Pin(1, nts::INPUT_PIN));
    list.push_back(new Pin(2, nts::INPUT_PIN));
    list.push_back(new Pin(3, nts::INPUT_PIN));
    list.push_back(new Pin(4, nts::INPUT_PIN));
    list.push_back(new Pin(5, nts::INPUT_PIN));
    list.push_back(new Pin(6, nts::INPUT_PIN));
    list.push_back(new Pin(7, nts::INPUT_PIN));
    list.push_back(new Pin(8, nts::INPUT_PIN));
    list.push_back(new Pin(9, nts::INPUT_PIN));
    list.push_back(new Pin(10, nts::INPUT_PIN));
    return list;
}

LoggerComponent::LoggerComponent(std::string name) :
    AComponent(std::move(name), getLoggerPins(), false)
{
}

nts::Tristate LoggerComponent::compute(__attribute__((unused))std::size_t pin)
{
    try {
        int8_t val = getPinValue();

        writeInLoggerFile(val);
        return nts::Undefined;
    } catch (const nts::LoggerPinUndefined& _) {
        return nts::Undefined;
    }
}

int8_t LoggerComponent::getPinValue()
{
    std::vector<nts::Tristate> values;
    int8_t res = 0;
    int idx = 0;

    if ((*this)[9]->pinCompute() != nts::True || (*this)[10]->pinCompute() != nts::False)
        throw nts::LoggerPinUndefined("Clock is not high or inhibit isn't false.");
    values.push_back((*this)[1]->pinCompute());
    values.push_back((*this)[2]->pinCompute());
    values.push_back((*this)[3]->pinCompute());
    values.push_back((*this)[4]->pinCompute());
    values.push_back((*this)[5]->pinCompute());
    values.push_back((*this)[6]->pinCompute());
    values.push_back((*this)[7]->pinCompute());
    values.push_back((*this)[8]->pinCompute());

    for (nts::Tristate state : values) {
        idx ++;
        if (state == nts::Undefined)
            throw nts::LoggerPinUndefined("Pin has value undefined in Logger component.");
        if (state == nts::False)
            continue;
        res += pow(2, idx - 1);
    }
    return res;
}

void LoggerComponent::writeInLoggerFile(char c)
{
    std::ofstream file("./log.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    file.write(&c, sizeof(c));

    if (!file.good()) {
        throw nts::LoggerFileWriteError("Could not write in file ./log.bin.");
    }
}
