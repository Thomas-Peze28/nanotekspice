/*
** EPITECH PROJECT, 2026
** include
** File description:
** NorComponent
*/

#ifndef NORCOMPONENTS_H
#define NORCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class NorComponent : public AComponent {
        public:
            NorComponent() = default;
            ~NorComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* NORCOMPONENTS_H */
