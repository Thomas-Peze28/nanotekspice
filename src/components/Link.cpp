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

nts::Link::Link(size_t otherPin, IComponent *otherComponent)
    : OtherPin(otherPin), OtherComponent(otherComponent)
{
}