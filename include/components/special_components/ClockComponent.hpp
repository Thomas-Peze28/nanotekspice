/*
** EPITECH PROJECT, 2026
** include
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_H
#define CLOCKCOMPONENT_H

#include "AComponent.hpp"

namespace nts {

    class ClockComponent : public AComponent {
        public:
            ClockComponent();
            ClockComponent(nts::Tristate value);
            ~ClockComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

            nts::Tristate getValue() const;
            void setValue(nts::Tristate value);

        private:
            nts::Tristate _value;
    };
}

#endif /* CLOCKCOMPONENT_H */
