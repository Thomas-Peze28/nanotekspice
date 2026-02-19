/*
** EPITECH PROJECT, 2026
** include
** File description:
** Circuit
*/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "AComponent.hpp"
#include "ComponentFactory.hpp"
#include <vector>
#include <memory>
#include <map>

namespace nts {

    class Circuit : public nts::IComponent {
        public:
            Circuit() = default;
            ~Circuit() = default;


            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

            void addComponent(const std::string& name, std::unique_ptr<nts::IComponent> component);
            nts::IComponent* getComponent(const std::string& name);
            void display(std::size_t tick);

        private:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
    
}

std::ostream& operator<<(std::ostream& os, const nts::Circuit& circuit);

#endif /* CIRCUIT_H */
