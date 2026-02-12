/*
** EPITECH PROJECT, 2026
** include
** File description:
** OrComponent
*/

#ifndef ORCOMPONENTS_H
#define ORCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class OrComponent : public AComponent {
        public:
            OrComponent() = default;
            ~OrComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* ORCOMPONENTS_H */
