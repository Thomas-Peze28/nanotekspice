/*
** EPITECH PROJECT, 2026
** project
** File description:
** AComponents
*/

#include "AComponent.hpp"

/*
** @brief NOT operation for input value.
** @param value The input value to negate.
** @return The negated value of the input.
*/
nts::Tristate operator!(nts::Tristate value)
{
    if (value == nts::Tristate::True)
        return nts::Tristate::False;
    else if (value == nts::Tristate::False)
        return nts::Tristate::True;
    else
        return nts::Tristate::Undefined;
}

/*
** @brief AND operation for two input values.
** @param val1 The first input value.
** @param val2 The second input value.
** @return The result of the AND operation on the two input values.
*/
nts::Tristate operator&&(nts::Tristate val1, nts::Tristate val2)
{
    if ((val1 == nts::Tristate::False) || (val2 == nts::Tristate::False))
        return nts::Tristate::False;
    else if ((val1 == nts::Tristate::True) && (val2 == nts::Tristate::True))
        return nts::Tristate::True;
    else
        return nts::Tristate::Undefined;
}

/*
** @brief OR operation for two input values.
** @param val1 The first input value.
** @param val2 The second input value.
** @return The result of the OR operation on the two input values.
*/
nts::Tristate operator||(nts::Tristate val1, nts::Tristate val2)
{
    if ((val1 == nts::Tristate::True) || (val2 == nts::Tristate::True))
        return nts::Tristate::True;
    else if ((val1 == nts::Tristate::False) && (val2 == nts::Tristate::False))
        return nts::Tristate::False;
    else
        return nts::Tristate::Undefined;
}

/*
** @brief XOR operation for two input values.
** @param val1 The first input value.
** @param val2 The second input value.
** @return The result of the XOR operation on the two input values.
*/
nts::Tristate operator^(nts::Tristate val1, nts::Tristate val2)
{
     if ((val1 == nts::Tristate::True && val2 == nts::Tristate::False) || (val1 == nts::Tristate::False && val2 == nts::Tristate::True))
        return nts::Tristate::True;
    else if ((val1 == nts::Tristate::True && val2 == nts::Tristate::True) || (val1 == nts::Tristate::False && val2 == nts::Tristate::False))
        return nts::Tristate::False;
    else
        return nts::Tristate::Undefined;
}

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

/*
** @brief Set a link between this component and another component.
** @param pin The pin number of this component to link.
** @param other The other component to link to.
** @param otherPin The pin number of the other component to link to.
*/
void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _links[pin] = nts::Link(otherPin, &other);
}

/*
** @brief Get the state of a linked component's pin.
** @param pin The pin number of this component to check the link for.
** @return The state of the linked component's pin, or Undefined if no link exists.
*/
nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    nts::Tristate state = nts::Tristate::Undefined;
    
    for (auto &link : _links) {
        if (link.first == pin) {
            state = link.second.OtherComponent->compute(link.second.OtherPin);
            break;
        }
    }
    return state;
}

std::ostream& operator<<(std::ostream& os, const nts::Tristate& tristate)
{
    switch (tristate) {
        case nts::Tristate::Undefined:
            os << "U";
            break;
        case nts::Tristate::True:
            os << "1";
            break;
        case nts::Tristate::False:
            os << "0";
            break;
    }
    return os;
}
