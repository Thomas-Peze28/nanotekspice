/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4513Component
*/

#ifndef COMPONENTS4513_H
#define COMPONENTS4513_H

#include "AComponent.hpp"

namespace nts {

    class Component4513 : public AComponent {
        public:
            Component4513() = default;
            ~Component4513() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENTS4513_H */