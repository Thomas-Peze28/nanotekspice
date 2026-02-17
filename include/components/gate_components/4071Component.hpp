/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4071Component
*/

#ifndef COMPONENTS4071_H
#define COMPONENTS4071_H

#include "AComponent.hpp"

namespace nts {

    class Component4071 : public AComponent {
        public:
            Component4071() = default;
            ~Component4071() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* COMPONENTS4071_H */