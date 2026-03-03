/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4512Component
*/

#ifndef COMPONENTS4512_H
#define COMPONENTS4512_H

#include "AComponent.hpp"

namespace nts {

    class Component4512 : public AComponent {
        public:
            Component4512() = default;
            ~Component4512() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENTS4512_H */