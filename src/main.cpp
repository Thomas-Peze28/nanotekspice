/*
** EPITECH PROJECT, 2026
** Project
** File description:
** main
*/

#include "NanoTekSpice.hpp"
#include <iostream>
#include <memory>


std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    if (v == nts::Tristate::True)
        s << "1";
    else if (v == nts::Tristate::False)
        s << "0";
    else
        s << "U";
    return s;
}

int main(void)
{
    nts::ComponentFactory factory;

    std::unique_ptr<nts::IComponent> gate = factory.createComponent("and");
    std::unique_ptr<nts::IComponent> input1 = factory.createComponent("false");
    std::unique_ptr<nts::IComponent> input2 = factory.createComponent("true");
    std::unique_ptr<nts::IComponent> inverter = factory.createComponent("not");

    gate->setLink(1, *input1, 1);
    gate->setLink(2, *input2, 1);
    inverter->setLink(1, *gate, 3);

    std::cout << "!(" << input1->compute(1) << " && " << input2->compute(1) << ") -> " << inverter->compute(2) << std::endl;
}