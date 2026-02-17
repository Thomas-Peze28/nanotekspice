/*
** EPITECH PROJECT, 2026
** Project
** File description:
** AndComponent
*/

#include "AndComponent.hpp"

/*
** @brief Compute the output of the AndComponent based on its input pins.
** @param pin The pin number to compute (should be 3 for the output).
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::AndComponent::compute(std::size_t pin)
{

    if (pin != 3)
        return nts::Tristate::Undefined;

    nts::Tristate input1 = getLink(1);
    nts::Tristate input2 = getLink(2);

    return input1 && input2;
}