/*
** EPITECH PROJECT, 2026
** include
** File description:
** TrueComponent
*/

#ifndef TRUECOMPONENTS_H
#define TRUECOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class TrueComponent : public AComponent {
        public:
            TrueComponent() = default;
            ~TrueComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* TRUECOMPONENTS_H */
