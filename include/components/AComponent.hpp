/*
** EPITECH PROJECT, 2026
** include
** File description:
** AComponents
*/

#ifndef ACOMPONENTS_H
#define ACOMPONENTS_H

#include "IComponent.hpp"
#include "Link.hpp"
#include <map>
#include <vector>
#include <iostream>

namespace nts {

    class AComponent : public IComponent {
        public:
            AComponent() = default;
            ~AComponent() = default;

            void simulate(std::size_t tick) override;

            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            nts::Tristate getLink(std::size_t pin);

        protected:
        private:
            std::vector<size_t> _pins;
            std::map<size_t , nts::Link> _links;
    };
}

nts::Tristate operator!(nts::Tristate value);
nts::Tristate operator&&(nts::Tristate val1, nts::Tristate val2);
nts::Tristate operator||(nts::Tristate val1, nts::Tristate val2);
nts::Tristate operator^(nts::Tristate val1, nts::Tristate val2);

std::ostream& operator<<(std::ostream& os, const nts::Tristate& tristate);

#endif /* ACOMPONENTS_H */
