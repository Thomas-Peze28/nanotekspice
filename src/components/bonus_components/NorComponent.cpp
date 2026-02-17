/*
** EPITECH PROJECT, 2026
** Project
** File description:
** NorComponent
*/

#include "NorComponent.hpp"

/*
** @brief Compute the output of the NorComponent based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::NorComponent::compute(std::size_t pin)
{

    if (pin != 3)
        return nts::Tristate::Undefined;

    nts::Tristate input1 = getLink(1);
    nts::Tristate input2 = getLink(2);

    return !(input1 || input2);
}