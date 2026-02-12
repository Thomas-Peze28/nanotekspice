/*
** EPITECH PROJECT, 2026
** include
** File description:
** NanoTekSpice
*/

#ifndef NANOTEKSPICE_H
#define NANOTEKSPICE_H

#include "IComponent.hpp"
#include "AComponent.hpp"
#include "Link.hpp"
#include "Circuit.hpp"
#include "ComponentFactory.hpp"

#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NotComponent.hpp"

class NanoTekSpice {
    public:
        NanoTekSpice() = default;
        ~NanoTekSpice() = default;
};


#endif /* NANOTEKSPICE_H */
