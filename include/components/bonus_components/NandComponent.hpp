/*
** EPITECH PROJECT, 2026
** include
** File description:
** NandComponent
*/

#ifndef NANDCOMPONENTS_H
#define NANDCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class NandComponent : public AComponent {
        public:
            NandComponent() = default;
            ~NandComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* NANDCOMPONENTS_H */
