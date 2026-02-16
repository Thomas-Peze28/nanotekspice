/*
** EPITECH PROJECT, 2026
** Project
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

/*
** @brief Compute the output of the OutputComponent based on its linked input.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;

    return getLink(1);
}