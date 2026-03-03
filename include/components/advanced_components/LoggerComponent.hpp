/*
** EPITECH PROJECT, 2026
** include
** File description:
** LoggerComponent
*/

#ifndef COMPONENTSLOGGER_H
#define COMPONENTSLOGGER_H

#include "AComponent.hpp"

namespace nts {

    class LoggerComponent : public AComponent {
        public:
            LoggerComponent() = default;
            ~LoggerComponent() = default;

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;
    };
}

#endif /* COMPONENTSLOGGER_H */