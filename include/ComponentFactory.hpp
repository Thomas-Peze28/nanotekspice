/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP
#define COMPONENTFACTORY_HPP

#include "IComponent.hpp"
#include <memory>
#include <string>
#include <map>
#include <functional>

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
#include "4069Component.hpp"
#include "4071Component.hpp"
#include "4081Component.hpp"
#include "4008Component.hpp"
#include "NandComponent.hpp"
#include "NorComponent.hpp"
#include "LoggerComponent.hpp"
#include "4512Component.hpp"

namespace nts
{
    class ComponentFactory
    {
    public:
        ComponentFactory();
        ~ComponentFactory() = default;

        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> get_creators() const;
        bool find_creator(const std::string &type);

    private:
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
    };
}

#endif /* COMPONENTFACTORY_HPP */