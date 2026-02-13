/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP
#define COMPONENTFACTORY_HPP

#include "NanoTekSpice.hpp"
#include <memory>
#include <string>
#include <map>
#include <functional>

namespace nts
{
    class ComponentFactory
    {
    public:
        ComponentFactory();
        ~ComponentFactory() = default;

        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

    private:
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
    };
}

#endif /* COMPONENTFACTORY_HPP */