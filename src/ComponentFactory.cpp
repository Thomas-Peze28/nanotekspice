/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** ComponentFactory
*/

#include "ComponentFactory.hpp"

/*
** @brief Construct a ComponentFactory and register component creators for each supported type.
*/
nts::ComponentFactory::ComponentFactory()
{
    _creators["input"] = []()
    {
        return std::make_unique<InputComponent>();
    };
    _creators["output"] = []()
    {
        return std::make_unique<OutputComponent>();
    };
    _creators["true"] = []()
    {
        return std::make_unique<TrueComponent>();
    };
    _creators["false"] = []()
    {
        return std::make_unique<FalseComponent>();
    };
    _creators["and"] = []()
    {
        return std::make_unique<AndComponent>();
    };
    _creators["or"] = []()
    {
        return std::make_unique<OrComponent>();
    };
    _creators["xor"] = []()
    {
        return std::make_unique<XorComponent>();
    };
    _creators["not"] = []()
    {
        return std::make_unique<NotComponent>();
    };
}

/*
** @brief Create a component of the specified type.
** @param type The type of component to create (e.g., "and", "or", "not", "input", "output", "true", "false").
** @return A unique pointer to the created component, or nullptr if the type is not recognized.
*/
std::unique_ptr<nts::IComponent> nts::ComponentFactory::createComponent(const std::string &type)
{
    auto it = _creators.find(type);

    if (it != _creators.end())
    {
        return it->second();
    }
    return nullptr;
}