/*
** EPITECH PROJECT, 2026
** include
** File description:
** AndComponent
*/

#ifndef ANDCOMPONENTS_H
#define ANDCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class AndComponent : public AComponent {
        public:
            AndComponent() = default;
            ~AndComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* ANDCOMPONENTS_H */
