/*
** EPITECH PROJECT, 2026
** Project
** File description:
** XorComponent
*/

#include "XorComponent.hpp"

nts::Tristate nts::XorComponent::compute(std::size_t pin)
{

    if (pin != 3)
        return nts::Tristate::Undefined;

    nts::Tristate input1 = getLink(1);
    nts::Tristate input2 = getLink(2);

    if ((input1 == nts::True && input2 == nts::False) || (input1 == nts::False && input2 == nts::True))
        return nts::Tristate::True;
    else if ((input1 == nts::True && input2 == nts::True) || (input1 == nts::False && input2 == nts::False))
        return nts::Tristate::False;
    else
        return nts::Tristate::Undefined;
}