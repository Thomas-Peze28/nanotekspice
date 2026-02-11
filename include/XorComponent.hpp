/*
** EPITECH PROJECT, 2026
** include
** File description:
** XorComponent
*/

#ifndef XORCOMPONENTS_H
#define XORCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class XorComponent : public AComponent {
        public:
            XorComponent() = default;
            ~XorComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* XORCOMPONENTS_H */
