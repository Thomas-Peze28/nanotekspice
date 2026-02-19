/*
** EPITECH PROJECT, 2026
** include
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENTS_H
#define INPUTCOMPONENTS_H

#include "AComponent.hpp"

namespace nts {

    class InputComponent : public AComponent {
        public:
            InputComponent();
            InputComponent(nts::Tristate value);
            ~InputComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate getValue() const;
            void setValue(nts::Tristate value);

            void simulate(std::size_t tick) override;

        private:
            nts::Tristate _value;
            nts::Tristate _nextValue;
    };
}

#endif /* INPUTCOMPONENTS_H */
