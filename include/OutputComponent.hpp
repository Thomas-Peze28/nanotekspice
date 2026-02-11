/*
** EPITECH PROJECT, 2026
** include
** File description:
** OutputComponent
*/

#ifndef OUTPUTCOMPONENTS_H
#define OUTPUTCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class OutputComponent : public AComponent {
        public:
            OutputComponent() = default;
            ~OutputComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
    };
}

#endif /* OUTPUTCOMPONENTS_H */
