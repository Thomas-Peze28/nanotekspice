/*
** EPITECH PROJECT, 2026
** Project
** File description:
** NotComponent
*/

#include "NotComponent.hpp"

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{

    if (pin != 2)
        return nts::Tristate::Undefined;

    nts::Tristate input = getLink(1);

    if (input == nts::True)
        return nts::False;
    else if (input == nts::False)
        return nts::True;
    else
        return nts::Undefined;
}