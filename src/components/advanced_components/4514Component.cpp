/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4514Component
*/

#include "4514Component.hpp"

/*
** @brief Compute the output of the 4514Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4514::compute(std::size_t pin)
{
    (void)pin;
    return nts::Tristate::Undefined;
}