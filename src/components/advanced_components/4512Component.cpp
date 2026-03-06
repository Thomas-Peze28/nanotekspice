/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4512Component
*/

#include "4512Component.hpp"

/*
** @brief Compute the output of the 4512Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4512::compute(std::size_t pin)
{
    if (pin != 14)
        return nts::Tristate::Undefined;

    std::size_t outputPins[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    nts::Tristate enable = getLink(15);
    if (enable == nts::Tristate::False || enable == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;

    nts::Tristate inhibit = getLink(10);
    if (inhibit == nts::Tristate::True)
        return nts::Tristate::False;
    if (inhibit == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;

    nts::Tristate in_a = getLink(11);
    nts::Tristate in_b = getLink(12);
    nts::Tristate in_c = getLink(13);
    
    if (in_a == nts::Tristate::Undefined || in_b == nts::Tristate::Undefined || in_c == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;

    int index = (in_a * 1) + (in_b * 2) + (in_c * 4);

    pin = outputPins[index];
    return getLink(pin);
}