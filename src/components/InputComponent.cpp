/*
** EPITECH PROJECT, 2026
** Project
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent() : _value(nts::Tristate::Undefined)
{
}

nts::InputComponent::InputComponent(nts::Tristate value) : _value(value)
{
}

nts::Tristate nts::InputComponent::getValue() const
{
    return _value;
}

void nts::InputComponent::setValue(nts::Tristate value)
{
    _value = value;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;

    return _value;
}