/*
** EPITECH PROJECT, 2026
** Project
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent() : _value(nts::Tristate::Undefined), _nextValue(nts::Tristate::Undefined)
{
}

/*
** @brief Construct an ClockComponent with the specified initial value.
** @param value The initial value of the ClockComponent (True, False, or Undefined).
*/
nts::ClockComponent::ClockComponent(nts::Tristate value) : _value(value), _nextValue(value)
{
}

/*
** @brief Get the current value of the ClockComponent.
** @return The current value of the ClockComponent (True, False, or Undefined).
*/
nts::Tristate nts::ClockComponent::getValue() const
{
    return _value;
}

/*
** @brief Set the value of the ClockComponent.
** @param value The new value to set for the ClockComponent (True, False, or Undefined).
*/
void nts::ClockComponent::setValue(nts::Tristate value)
{
    _nextValue = value;
}

/*
** @brief Compute the output of the ClockComponent, which is determined by its internal value.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid.
*/
nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Tristate::Undefined;

    return _value;
}

/*
** @brief Simulate the behavior of the ClockComponent by toggling its value based on the tick count.
** @param tick The current simulation tick count, used to determine the state of the clock.
*/
void nts::ClockComponent::simulate(std::size_t tick)
{
    (void)tick;

    _value = _nextValue;

    if (_value == nts::Tristate::True)
        _nextValue = nts::Tristate::False;
    else if (_value == nts::Tristate::False)
        _nextValue = nts::Tristate::True;
    else
        _nextValue = nts::Tristate::Undefined;
}