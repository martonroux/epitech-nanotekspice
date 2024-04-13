/*
** EPITECH PROJECT, 2024
** nanotekspice
** File description:
** Errors.hpp
*/

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <string>

namespace nts {
    class Error : public std::exception {
        std::string _msg;

    public:
        explicit Error(std::string msg) : _msg(std::move(msg)) {}
        const char * what() const noexcept override;
    };

    class ComponentError : public Error {
    public:
        explicit ComponentError(std::string msg) : Error(std::move(msg)) {}
    };

    class PinConnectionError : public Error {
    public:
        explicit PinConnectionError(std::string msg) : Error(std::move(msg)) {}
    };

    class CircuitGeneratorError : public Error {
    public:
        explicit CircuitGeneratorError(std::string msg) : Error(std::move(msg)) {}
    };

    class FileNotFound : public Error {
    public:
        explicit FileNotFound(std::string msg) : Error(std::move(msg)) {}
    };

    class InvalidFile : public Error {
    public:
        explicit InvalidFile(std::string msg) : Error(std::move(msg)) {}
    };

    class InvalidComponent : public Error {
    public:
        explicit InvalidComponent(std::string msg) : Error(std::move(msg)) {}
    };

    class InvalidAssignement : public Error {
        public:
        explicit InvalidAssignement(std::string msg) : Error(std::move(msg)) {}
    };

    class ComponentNotFound : public Error {
    public:
        explicit ComponentNotFound(std::string msg) : Error(std::move(msg)) {}
    };

    class ComponentNameDuplicate : public Error {
    public:
        explicit ComponentNameDuplicate(std::string msg) : Error(std::move(msg)) {}
    };

    class CommandNotFound : public Error {
    public:
        explicit CommandNotFound(std::string msg) : Error(std::move(msg)) {}
    };

    class LoggerPinUndefined : public Error {
    public:
        explicit LoggerPinUndefined(std::string msg) : Error(std::move(msg)) {}
    };

    class LoggerFileWriteError : public Error {
    public:
        explicit LoggerFileWriteError(std::string msg) : Error(std::move(msg)) {}
    };

    class NoRAMSelect : public Error {
    public:
        explicit NoRAMSelect(std::string msg) : Error(std::move(msg)) {}
    };

    class RomFileNotFound : public Error {
        public:
            explicit RomFileNotFound(std::string msg) : Error(std::move(msg)) {}
    };
}

#endif
