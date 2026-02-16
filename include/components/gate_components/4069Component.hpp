/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4069Component
*/

#ifndef COMPONENTS4069_H
#define COMPONENTS4069_H

#include "AComponent.hpp"

namespace nts {

    class Component4069 : public AComponent {
        public:
            Component4069() = default;
            ~Component4069() = default;

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate computeNot(nts::Tristate input);
    };
}

#endif /* COMPONENTS4069_H */