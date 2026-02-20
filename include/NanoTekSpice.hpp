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
#include "Parsing.hpp"

namespace nts
{
    class NanoTekSpice
    {
    public:
        NanoTekSpice() = default;
        ~NanoTekSpice() = default;

        int run(int argc, char **argv);
        void shell();

        bool buildCircuit(const std::string &file_name);

    private:
        Circuit _circuit;
        ComponentFactory _factory;
        Parsing _parser;
    };
}

#endif /* NANOTEKSPICE_H */
