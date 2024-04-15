cmake_minimum_required(VERSION 3.25)
project(nanotekspice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Werror")

include_directories(include)

execute_process(COMMAND cp -r ../circuits ./circuits)

add_executable(nanotekspice
        include/components/elementary/AndComponent.hpp
        include/components/elementary/LogicComponent.hpp
        include/components/elementary/OrComponent.hpp
        include/components/elementary/XorComponent.hpp
        include/components/special/FalseComponent.hpp
        include/components/special/InputComponent.hpp
        include/components/elementary/NotComponent.hpp
        include/components/special/TrueComponent.hpp
        include/components/AComponent.hpp
        include/components/Pin.hpp
        include/parser/Parser.hpp
        include/parser/ParseUtils.hpp
        include/circuit/Circuit.hpp
        include/Enums.hpp
        include/IComponent.hpp
        src/main.cpp
        src/components/elementary/AndComponent.cpp
        src/components/elementary/LogicComponent.cpp
        src/components/elementary/OrComponent.cpp
        src/components/elementary/XorComponent.cpp
        src/components/special/FalseComponent.cpp
        src/components/special/InputComponent.cpp
        src/components/elementary/NotComponent.cpp
        src/components/special/TrueComponent.cpp
        src/components/AComponent.cpp
        src/components/Pin.cpp
        src/parser/Parser.cpp
        src/parser/ParseUtils.cpp
        src/circuit/Circuit.cpp
        src/components/special/OutputComponent.cpp
        src/circuit/CircuitGenerator.cpp
        src/Errors.cpp
        src/Simulator.cpp
        include/Simulator.hpp
        include/components/special/ClockComponent.hpp
        src/components/special/ClockComponent.cpp
        src/components/IOComponent.cpp
        include/components/IOComponent.hpp
        src/components/special/LoggerComponent.cpp
        include/components/special/LoggerComponent.hpp
        src/components/advanced/RomComponent.cpp
        include/components/advanced/RomComponent.hpp
        include/components/elementary/InhibitComponent.hpp
        src/components/elementary/InhibitComponent.cpp
        src/components/advanced/JohnsonComponent.cpp
        include/components/advanced/JohnsonComponent.hpp
)
