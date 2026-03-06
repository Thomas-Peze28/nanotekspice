/*
** EPITECH PROJECT, 2026
** include
** File description:
** 4514Component
*/

#ifndef COMPONENTS4514_H
#define COMPONENTS4514_H

#include "AComponent.hpp"

namespace nts {

    class Component4514 : public AComponent {
        public:
            Component4514();
            ~Component4514() = default;

            nts::Tristate compute(std::size_t pin) override;
        
        private:
            int _latch;
    };
}

#endif /* COMPONENTS4514_H */