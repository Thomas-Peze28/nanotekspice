/*
** EPITECH PROJECT, 2026
** Project
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;

    return getLink(1);
}