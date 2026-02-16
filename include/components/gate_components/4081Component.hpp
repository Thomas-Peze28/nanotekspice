/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4081Component
*/

#ifndef COMPONENTS4081_H
#define COMPONENTS4081_H

#include "AComponent.hpp"

namespace nts {

    class Component4081 : public AComponent {
        public:
            Component4081() = default;
            ~Component4081() = default;

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate computeAnd(nts::Tristate input1, nts::Tristate input2);
    };
}

#endif /* COMPONENTS4081_H */