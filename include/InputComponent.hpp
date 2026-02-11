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

        private:
            nts::Tristate _value;
    };
}

#endif /* INPUTCOMPONENTS_H */
