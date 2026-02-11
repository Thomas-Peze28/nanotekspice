/*
** EPITECH PROJECT, 2026
** Project
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;
    return nts::Tristate::True;
}