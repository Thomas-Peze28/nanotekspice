/*
** EPITECH PROJECT, 2026
** include
** File description:
** NotComponent
*/

#ifndef NOTCOMPONENT_H
#define NOTCOMPONENT_H

#include "AComponent.hpp"

namespace nts {

    class NotComponent : public AComponent {
        public:
            NotComponent() = default;
            ~NotComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* NOTCOMPONENT_H */
