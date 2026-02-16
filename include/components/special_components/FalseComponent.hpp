/*
** EPITECH PROJECT, 2026
** include
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENTS_H
#define FALSECOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class FalseComponent : public AComponent {
        public:
            FalseComponent() = default;
            ~FalseComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* FALSECOMPONENTS_H */
