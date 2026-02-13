/*
** EPITECH PROJECT, 2026
** Project
** File description:
** OrComponent
*/

#include "OrComponent.hpp"

/*
** @brief Compute the output of the OrComponent based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::OrComponent::compute(std::size_t pin)
{

    if (pin != 3)
        return nts::Tristate::Undefined;

    nts::Tristate input1 = getLink(1);
    nts::Tristate input2 = getLink(2);

    if (input1 == nts::True || input2 == nts::True)
        return nts::Tristate::True;
    else if (input1 == nts::False && input2 == nts::False)
        return nts::Tristate::False;
    else
        return nts::Tristate::Undefined;
    
}