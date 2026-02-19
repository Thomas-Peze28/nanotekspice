/*
** EPITECH PROJECT, 2026
** Project
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent() : _value(nts::Tristate::Undefined), _nextValue(nts::Tristate::Undefined)
{
}

/*
** @brief Construct an InputComponent with the specified initial value.
** @param value The initial value of the InputComponent (True, False, or Undefined).
*/
nts::InputComponent::InputComponent(nts::Tristate value) : _value(value), _nextValue(value)
{
}

/*
** @brief Get the current value of the InputComponent.
** @return The current value of the InputComponent (True, False, or Undefined).
*/
nts::Tristate nts::InputComponent::getValue() const
{
    return _value;
}

/*
** @brief Set the value of the InputComponent.
** @param value The new value to set for the InputComponent (True, False, or Undefined).
*/
void nts::InputComponent::setValue(nts::Tristate value)
{
    _nextValue = value;
}

/*
** @brief Compute the output of the InputComponent, which is determined by its internal value.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;

    return _value;
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;

    _value = _nextValue;
}