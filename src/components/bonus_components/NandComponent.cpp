/*
** EPITECH PROJECT, 2026
** Project
** File description:
** NandComponent
*/

#include "NandComponent.hpp"

/*
** @brief Compute the output of the NandComponent based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::NandComponent::compute(std::size_t pin)
{

    if (pin != 3)
        return nts::Tristate::Undefined;

    nts::Tristate input1 = getLink(1);
    nts::Tristate input2 = getLink(2);

    return !(input1 && input2);
}