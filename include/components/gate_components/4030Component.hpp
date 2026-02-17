/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4030Component
*/

#ifndef COMPONENTS4030_H
#define COMPONENTS4030_H

#include "AComponent.hpp"

namespace nts {

    class Component4030 : public AComponent {
        public:
            Component4030() = default;
            ~Component4030() = default;

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate computeXor(nts::Tristate input1, nts::Tristate input2);
    };
}

#endif /* COMPONENTS4030_H */