/*
** EPITECH PROJECT, 2026
** Project
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

/*
** @brief Compute the output of the FalseComponent, which is always False.
** @param pin The pin number to compute (should be 1 for the output).
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;
    return nts::Tristate::False;
}