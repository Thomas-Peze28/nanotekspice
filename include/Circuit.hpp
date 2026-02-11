/*
** EPITECH PROJECT, 2026
** include
** File description:
** Circuit
*/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "IComponent.hpp"
#include <list>
#include <memory>

namespace nts {

    class Circuit {
        public:
            Circuit() = default;
            ~Circuit() = default;

        private:
            std::vector<std::unique_ptr<nts::IComponent>> _components;
    };
    
}

#endif /* CIRCUIT_H */
