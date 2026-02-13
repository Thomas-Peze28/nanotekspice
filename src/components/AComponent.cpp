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

/*
** @brief Set a link between this component and another component.
** @param pin The pin number of this component to link.
** @param other The other component to link to.
** @param otherPin The pin number of the other component to link to.
*/
void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _links[pin] = nts::Link(otherPin, &other);
}

/*
** @brief Get the state of a linked component's pin.
** @param pin The pin number of this component to check the link for.
** @return The state of the linked component's pin, or Undefined if no link exists.
*/
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


