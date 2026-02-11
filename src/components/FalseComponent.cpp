/*
** EPITECH PROJECT, 2026
** Project
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;
    return nts::Tristate::False;
}