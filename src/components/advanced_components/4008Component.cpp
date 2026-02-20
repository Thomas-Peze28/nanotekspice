/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4008Component
*/

#include "4008Component.hpp"

nts::Tristate nts::Component4008::computeSum(nts::Tristate a, nts::Tristate b, nts::Tristate carryIn)
{
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined || carryIn == nts::Tristate::Undefined) {
        return nts::Tristate::Undefined;
    }
    return (a ^ b ^ carryIn);
}

nts::Tristate nts::Component4008::computeCarry(nts::Tristate a, nts::Tristate b, nts::Tristate carryIn)
{
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined || carryIn == nts::Tristate::Undefined) {
        return nts::Tristate::Undefined;
    }
    return (nts::Tristate)((a & b) | (carryIn & (a ^ b)));
}

/*
** @brief Compute the output of the 4008Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4008::compute(std::size_t pin)
{
    nts::Tristate c1 = getLink(9);

    nts::Tristate a1 = getLink(7);
    nts::Tristate b1 = getLink(6);
    nts::Tristate c2 = computeCarry(a1, b1, c1); 

    nts::Tristate a2 = getLink(5);
    nts::Tristate b2 = getLink(4);
    nts::Tristate c3 = computeCarry(a2, b2, c2);

    nts::Tristate a3 = getLink(3);
    nts::Tristate b3 = getLink(2);
    nts::Tristate c4 = computeCarry(a3, b3, c3);

    nts::Tristate a4 = getLink(1);
    nts::Tristate b4 = getLink(15);
    nts::Tristate c5 = computeCarry(a4, b4, c4);

    if (pin == 10)
        return computeSum(a1, b1, c1);
    if (pin == 11)
        return computeSum(a2, b2, c2);
    if (pin == 12)
        return computeSum(a3, b3, c3);
    if (pin == 13)
        return computeSum(a4, b4, c4);
    if (pin == 14)
        return c5;

    return nts::Undefined;
}