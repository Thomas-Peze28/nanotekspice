/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4001Component
*/

#include "4001Component.hpp"

/*
** @brief Compute the output of the 4001Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4001::compute(std::size_t pin)
{
    if (pin == 3)
        return !(getLink(1) || getLink(2));
    if (pin == 4)
        return !(getLink(5) || getLink(6));
    if (pin == 10)
        return !(getLink(8) || getLink(9));
    if (pin == 11)
        return !(getLink(12) || getLink(13));
    return nts::Undefined;
}