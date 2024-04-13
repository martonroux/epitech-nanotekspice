//
// Created by Guillaume Tran on 05/02/2024.
//

#include "components/elementary/LogicComponent.hpp"
#include "components/elementary/AndComponent.hpp"

AndComponent::AndComponent(const std::string name) : LogicComponent(name) {
    _truthTable = {
        {{nts::Tristate::True, nts::Tristate::True}, nts::Tristate::True},
        {{nts::Tristate::True, nts::Tristate::False}, nts::Tristate::False},
        {{nts::Tristate::False, nts::Tristate::True}, nts::Tristate::False},
        {{nts::Tristate::False, nts::Tristate::False}, nts::Tristate::False},
        {{nts::Tristate::True, nts::Tristate::Undefined}, nts::Tristate::Undefined},
        {{nts::Tristate::Undefined, nts::Tristate::True}, nts::Tristate::Undefined},
        {{nts::Tristate::False, nts::Tristate::Undefined}, nts::Tristate::False},
        {{nts::Tristate::Undefined, nts::Tristate::False}, nts::Tristate::False},
        {{nts::Tristate::Undefined, nts::Tristate::Undefined}, nts::Tristate::Undefined}
    };
}
