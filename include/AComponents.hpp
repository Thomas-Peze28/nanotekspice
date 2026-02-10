/*
** EPITECH PROJECT, 2026
** include
** File description:
** AComponents
*/

#ifndef ACOMPONENTS_H
#define ACOMPONENTS_H

#include "IComponents.hpp"

namespace nts {

    class AComponent : public IComponent {
        public:
            virtual ~AComponent() = default;

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
    };
}

#endif /* ACOMPONENTS_H */
