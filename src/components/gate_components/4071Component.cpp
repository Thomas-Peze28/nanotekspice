/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4071Component
*/

#include "4071Component.hpp"

/*
** @brief Compute the output of the 4071Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4071::compute(std::size_t pin)
{
    if (pin == 3)
        return computeOr(getLink(1), getLink(2));
    if (pin == 4)
        return computeOr(getLink(5), getLink(6));
    if (pin == 10)
        return computeOr(getLink(8), getLink(9));
    if (pin == 11)
        return computeOr(getLink(12), getLink(13));
    return nts::Undefined;
}

/*
** @brief Compute the OR operation for two input signals.
** @param input1 The first input signal.
** @param input2 The second input signal.
** @return The result of the OR operation.
*/
nts::Tristate nts::Component4071::computeOr(nts::Tristate input1, nts::Tristate input2)
{
    if (input1 == nts::True || input2 == nts::True)
        return nts::True;
    else if (input1 == nts::Undefined || input2 == nts::Undefined)
        return nts::Undefined;
    else
        return nts::False;
}
