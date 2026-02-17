/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4069Component
*/

#include "4069Component.hpp"

/*
** @brief Compute the output of the 4069Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4069::compute(std::size_t pin)
{
    if (pin == 2)
        return !getLink(1);
    if (pin == 4)
        return !getLink(3);
    if (pin == 6)
        return !getLink(5);
    if (pin == 8)
        return !getLink(9);
    if (pin == 10)
        return !getLink(11);
    if (pin == 12)
        return !getLink(13);
    return nts::Undefined;
}
