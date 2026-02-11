/*
** EPITECH PROJECT, 2026
** project
** File description:
** AComponents
*/

#include "AComponent.hpp"

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _links[pin] = nts::Link(otherPin, &other);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    nts::Tristate state;
    
    for (auto &link : _links) {
        if (link.first == pin) {
            state = link.second.OtherComponent->compute(link.second.OtherPin);
            break;
        }
    }
    return state;
}


