/*
** EPITECH PROJECT, 2024
** NanoTeckSpice
** File description:
** main.cpp
*/

#include "../include/Simulator.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Not enough / too much arguments (expected 1: nts file path)." << std::endl;
        return 84;
    }
    try {
        Simulator sim(av[1]);
        if (sim.run() == 1) {
            return 0;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
