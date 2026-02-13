/*
** EPITECH PROJECT, 2026
** Project
** File description:
** Link
*/

#include "Link.hpp"

nts::Link::Link()
    : OtherPin(0), OtherComponent(nullptr)
{
}

/*
** @brief Construct a Link object with the specified other pin and component.
** @param otherPin The pin number of the other component to link to.
** @param otherComponent A pointer to the other component to link to.
*/
nts::Link::Link(size_t otherPin, IComponent *otherComponent)
    : OtherPin(otherPin), OtherComponent(otherComponent)
{
}