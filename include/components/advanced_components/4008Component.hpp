/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4008Component
*/

#ifndef COMPONENTS4008_H
#define COMPONENTS4008_H

#include "AComponent.hpp"

namespace nts {

    class Component4008 : public AComponent {
        public:
            Component4008() = default;
            ~Component4008() = default;

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate computeSum(nts::Tristate a, nts::Tristate b, nts::Tristate carryIn);
            nts::Tristate computeCarry(nts::Tristate a, nts::Tristate b, nts::Tristate carryIn);
    };
}

#endif /* COMPONENTS4008_H */