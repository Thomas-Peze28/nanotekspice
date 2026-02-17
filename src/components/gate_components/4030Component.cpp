/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4030Component
*/

#include "4030Component.hpp"

/*
** @brief Compute the output of the 4030Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4030::compute(std::size_t pin)
{
    if (pin == 3)
        return computeXor(getLink(1), getLink(2));
    if (pin == 4)
        return computeXor(getLink(5), getLink(6));
    if (pin == 10)
        return computeXor(getLink(8), getLink(9));
    if (pin == 11)
        return computeXor(getLink(12), getLink(13));
    return nts::Undefined;
}

/*
** @brief Compute the XOR operation for two input signals.
** @param input1 The first input signal.
** @param input2 The second input signal.
** @return The result of the XOR operation.
*/
nts::Tristate nts::Component4030::computeXor(nts::Tristate input1, nts::Tristate input2)
{
    if ((input1 == nts::True && input2 == nts::False) || (input1 == nts::False && input2 == nts::True))
        return nts::True;
    else if ((input1 == nts::True && input2 == nts::True) || (input1 == nts::False && input2 == nts::False))
        return nts::False;
    else
        return nts::Undefined;
}
