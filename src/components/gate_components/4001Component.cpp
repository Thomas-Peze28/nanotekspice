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
        return computeNor(getLink(1), getLink(2));
    if (pin == 4)
        return computeNor(getLink(5), getLink(6));
    if (pin == 10)
        return computeNor(getLink(8), getLink(9));
    if (pin == 11)
        return computeNor(getLink(12), getLink(13));
    return nts::Undefined;
}

/*
** @brief Compute the NOR operation for two input signals.
** @param input1 The first input signal.
** @param input2 The second input signal.
** @return The result of the NOR operation.
*/
nts::Tristate nts::Component4001::computeNor(nts::Tristate input1, nts::Tristate input2)
{
    if (input1 == nts::True || input2 == nts::True)
        return nts::False;
    else if (input1 == nts::False && input2 == nts::False)
        return nts::True;
    else
        return nts::Undefined;
}