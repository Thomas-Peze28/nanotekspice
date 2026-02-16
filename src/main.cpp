/*
** EPITECH PROJECT, 2026
** Project
** File description:
** main
*/

#include "NanoTekSpice.hpp"
#include "ClockComponent.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>


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

namespace {
    struct BinaryCase {
        nts::Tristate a;
        nts::Tristate b;
        nts::Tristate expected;
        const char *label;
    };

    struct UnaryCase {
        nts::Tristate a;
        nts::Tristate expected;
        const char *label;
    };

    void printCheck(const std::string &label, nts::Tristate got, nts::Tristate expected)
    {
        std::cout << label << " -> got=" << got << " expected=" << expected;
        if (got == expected)
            std::cout << " [OK]";
        else
            std::cout << " [KO]";
        std::cout << std::endl;
    }

    nts::InputComponent *asInput(const std::unique_ptr<nts::IComponent> &ptr)
    {
        return dynamic_cast<nts::InputComponent *>(ptr.get());
    }

    void testBinaryGate(nts::ComponentFactory &factory, const std::string &type,
        const std::vector<BinaryCase> &cases)
    {
        for (const auto &tcase : cases) {
            auto gate = factory.createComponent(type);
            auto input1 = factory.createComponent("input");
            auto input2 = factory.createComponent("input");
            auto output = factory.createComponent("output");

            auto *in1 = asInput(input1);
            auto *in2 = asInput(input2);
            if (!gate || !in1 || !in2 || !output) {
                std::cout << type << " " << tcase.label << " -> setup failed" << std::endl;
                continue;
            }

            in1->setValue(tcase.a);
            in2->setValue(tcase.b);
            gate->setLink(1, *input1, 1);
            gate->setLink(2, *input2, 1);
            output->setLink(1, *gate, 3);

            printCheck(type + " " + tcase.label, output->compute(1), tcase.expected);
        }
    }

    void testUnaryGate(nts::ComponentFactory &factory, const std::string &type,
        const std::vector<UnaryCase> &cases)
    {
        for (const auto &tcase : cases) {
            auto gate = factory.createComponent(type);
            auto input = factory.createComponent("input");
            auto output = factory.createComponent("output");

            auto *in1 = asInput(input);
            if (!gate || !in1 || !output) {
                std::cout << type << " " << tcase.label << " -> setup failed" << std::endl;
                continue;
            }

            in1->setValue(tcase.a);
            gate->setLink(1, *input, 1);
            output->setLink(1, *gate, 2);

            printCheck(type + " " + tcase.label, output->compute(1), tcase.expected);
        }
    }
}

int main(void)
{
    nts::ComponentFactory factory;

    std::cout << "== Constants ==" << std::endl;
    {
        auto tconst = factory.createComponent("true");
        auto fconst = factory.createComponent("false");
        printCheck("true pin1", tconst->compute(1), nts::Tristate::True);
        printCheck("false pin1", fconst->compute(1), nts::Tristate::False);
        printCheck("true pin2", tconst->compute(2), nts::Tristate::Undefined);
        printCheck("false pin2", fconst->compute(2), nts::Tristate::Undefined);
    }

    std::cout << "\n== Input / Output ==" << std::endl;
    {
        auto input = factory.createComponent("input");
        auto output = factory.createComponent("output");
        auto *in = asInput(input);

        if (in && output) {
            in->setValue(nts::Tristate::True);
            output->setLink(1, *input, 1);
            printCheck("input true", output->compute(1), nts::Tristate::True);

            in->setValue(nts::Tristate::False);
            printCheck("input false", output->compute(1), nts::Tristate::False);

            in->setValue(nts::Tristate::Undefined);
            printCheck("input U", output->compute(1), nts::Tristate::Undefined);
        }
    }

    std::cout << "\n== NOT ==" << std::endl;
    testUnaryGate(factory, "not", {
        {nts::Tristate::True, nts::Tristate::False, "T"},
        {nts::Tristate::False, nts::Tristate::True, "F"},
        {nts::Tristate::Undefined, nts::Tristate::Undefined, "U"}
    });

    std::cout << "\n== AND ==" << std::endl;
    testBinaryGate(factory, "and", {
        {nts::Tristate::True, nts::Tristate::True, nts::Tristate::True, "T/T"},
        {nts::Tristate::True, nts::Tristate::False, nts::Tristate::False, "T/F"},
        {nts::Tristate::False, nts::Tristate::False, nts::Tristate::False, "F/F"},
        {nts::Tristate::Undefined, nts::Tristate::True, nts::Tristate::Undefined, "U/T"}
    });

    std::cout << "\n== OR ==" << std::endl;
    testBinaryGate(factory, "or", {
        {nts::Tristate::True, nts::Tristate::True, nts::Tristate::True, "T/T"},
        {nts::Tristate::True, nts::Tristate::False, nts::Tristate::True, "T/F"},
        {nts::Tristate::False, nts::Tristate::False, nts::Tristate::False, "F/F"},
        {nts::Tristate::Undefined, nts::Tristate::False, nts::Tristate::Undefined, "U/F"}
    });

    std::cout << "\n== XOR ==" << std::endl;
    testBinaryGate(factory, "xor", {
        {nts::Tristate::True, nts::Tristate::True, nts::Tristate::False, "T/T"},
        {nts::Tristate::True, nts::Tristate::False, nts::Tristate::True, "T/F"},
        {nts::Tristate::False, nts::Tristate::False, nts::Tristate::False, "F/F"},
        {nts::Tristate::Undefined, nts::Tristate::True, nts::Tristate::Undefined, "U/T"}
    });

    std::cout << "\n== Composite Circuit ==" << std::endl;
    {
        auto in1 = factory.createComponent("input");
        auto in2 = factory.createComponent("input");
        auto gate = factory.createComponent("and");
        auto inv = factory.createComponent("not");
        auto out = factory.createComponent("output");

        auto *input1 = asInput(in1);
        auto *input2 = asInput(in2);

        if (input1 && input2 && gate && inv && out) {
            input1->setValue(nts::Tristate::False);
            input2->setValue(nts::Tristate::True);

            gate->setLink(1, *in1, 1);
            gate->setLink(2, *in2, 1);
            inv->setLink(1, *gate, 3);
            out->setLink(1, *inv, 2);

            printCheck("!(F && T)", out->compute(1), nts::Tristate::True);
        }
    }

    std::cout << "\n== Clock ==" << std::endl;
    {
        nts::ClockComponent clock(nts::Tristate::Undefined);
        auto output = factory.createComponent("output");
        if (output) {
            output->setLink(1, clock, 1);
            for (std::size_t tick = 0; tick < 4; ++tick) {
                clock.simulate(tick);
                std::cout << "tick " << tick << " -> clock=" << output->compute(1) << std::endl;
            }
        }
    }

    return 0;
}