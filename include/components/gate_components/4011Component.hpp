/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4011Component
*/

#ifndef COMPONENTS4011_H
#define COMPONENTS4011_H

#include "AComponent.hpp"

namespace nts {

    class Component4011 : public AComponent {
        public:
            Component4011() = default;
            ~Component4011() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENTS4011_H */