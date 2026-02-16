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
#include "ClockComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NotComponent.hpp"
#include "4001Component.hpp"
#include "4011Component.hpp"
#include "4030Component.hpp"
#include "4071Component.hpp"
#include "4081Component.hpp"
#include "NandComponent.hpp"
#include "NorComponent.hpp"

class NanoTekSpice {
    public:
        NanoTekSpice() = default;
        ~NanoTekSpice() = default;
};


#endif /* NANOTEKSPICE_H */
