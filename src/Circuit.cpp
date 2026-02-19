#include "Circuit.hpp"
#include <iostream>

void nts::Circuit::addComponent(const std::string &name, std::unique_ptr<nts::IComponent> component)
{
    _components[name] = std::move(component);
}

nts::IComponent *nts::Circuit::getComponent(const std::string &name)
{
    if (_components.find(name) != _components.end())
    {
        return _components[name].get();
    }
    return nullptr;
}

void nts::Circuit::display(std::size_t tick)
{
    std::cout << "tick: " << tick << std::endl;

    std::cout << "input(s):" << std::endl;
    for (auto &[name, component] : _components)
    {
        if (dynamic_cast<nts::InputComponent *>(component.get()) != nullptr)
        {
            std::cout << "    "  << name << ": " << component->compute(1) << std::endl;
        }
    }

    std::cout << "output(s):" << std::endl;
    for (auto &[name, component] : _components)
    {
        if (dynamic_cast<nts::OutputComponent *>(component.get()) != nullptr)
        {
            std::cout << "    " << name << ": " << component->compute(1) << std::endl;
        }
    }
    return;
}

void nts::Circuit::simulate(std::size_t tick)
{
    for (auto &[name, component] : _components)
    {
        component->simulate(tick);
    }
}

nts::Tristate nts::Circuit::compute(std::size_t pin)
{
    (void)pin;
    return nts::Undefined;
}

void nts::Circuit::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    (void)pin;
    (void)other;
    (void)otherPin;
}

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit)
{
    (void)circuit;
    os << "Circuit" << std::endl;
    return os;
}