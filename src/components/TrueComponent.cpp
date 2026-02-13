/*
** EPITECH PROJECT, 2026
** Project
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

/*
** @brief Compute the output of the TrueComponent, which is always True.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;
    return nts::Tristate::True;
}