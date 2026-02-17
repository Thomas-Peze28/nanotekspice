/*
** EPITECH PROJECT, 2026
** Project
** File description:
** NotComponent
*/

#include "NotComponent.hpp"

/*
** @brief Compute the output of the NotComponent based on its input pin.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::NotComponent::compute(std::size_t pin)
{

    if (pin != 2)
        return nts::Tristate::Undefined;

    nts::Tristate input = getLink(1);

    return !input;
}