/*
** EPITECH PROJECT, 2026
** include
** File description:
** Link
*/

#ifndef LINK_H
#define LINK_H

#include "IComponent.hpp"
#include <map>

namespace nts {

    class Link {
        public:
            Link();
            Link(size_t otherPin, IComponent *otherComponent);

            size_t OtherPin;
            IComponent *OtherComponent;
    };
}

#endif /* LINK_H */
