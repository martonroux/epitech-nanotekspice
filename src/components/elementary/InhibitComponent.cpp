//
// Created by Guillaume Tran on 01/03/2024.
//

#include "components/elementary/InhibitComponent.hpp"

InhibitComponent::InhibitComponent(const std::string name) : LogicComponent(name) {
    _truthTable = {
            {{nts::Tristate::True, nts::Tristate::True}, nts::Tristate::False},
            {{nts::Tristate::False, nts::Tristate::True}, nts::Tristate::False},
            {{nts::Tristate::True, nts::Tristate::False}, nts::Tristate::True},
            {{nts::Tristate::False, nts::Tristate::False}, nts::Tristate::False},
            {{nts::Tristate::True, nts::Tristate::Undefined}, nts::Tristate::Undefined},
            {{nts::Tristate::Undefined, nts::Tristate::True}, nts::Tristate::Undefined},
            {{nts::Tristate::False, nts::Tristate::Undefined}, nts::Tristate::False},
            {{nts::Tristate::Undefined, nts::Tristate::False}, nts::Tristate::False},
            {{nts::Tristate::Undefined, nts::Tristate::Undefined}, nts::Tristate::Undefined}
    };
}