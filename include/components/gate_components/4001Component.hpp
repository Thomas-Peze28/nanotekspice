/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4001Component
*/

#ifndef COMPONENTS4001_H
#define COMPONENTS4001_H

#include "AComponent.hpp"

namespace nts {

    class Component4001 : public AComponent {
        public:
            Component4001() = default;
            ~Component4001() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENTS4001_H */