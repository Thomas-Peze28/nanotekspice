/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_true
*/

#include <criterion/criterion.h>
#include "FalseComponent.hpp"
#include "OutputComponent.hpp"
#include "AndComponent.hpp"
#include "InputComponent.hpp"

Test(components, false_components_constant) {
	nts::FalseComponent f_comp;

	cr_assert_eq(f_comp.compute(1), nts::Tristate::False);
	cr_assert_eq(f_comp.compute(2), nts::Tristate::Undefined);
}

Test(components, false_component_persistence) {
    nts::FalseComponent f_comp;

    // État initial
    cr_assert_eq(f_comp.compute(1), nts::Tristate::False);

    // On simule plusieurs cycles
    for (int i = 0; i < 10; ++i) {
        f_comp.simulate(i);
        cr_assert_eq(f_comp.compute(1), nts::Tristate::False, "FalseComponent changed at tick %d", i);
    }
}

Test(components, false_comp_integration_and) {
    nts::AndComponent and_gate;
    nts::FalseComponent gnd; // Souvent utilisé comme Ground
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // On lie une entrée au FalseComponent
    and_gate.setLink(1, gnd, 1);
    and_gate.setLink(2, in_undef, 1);

    // False & Undefined = False (Propriété de dominance du False)
    cr_assert_eq(and_gate.compute(3), nts::Tristate::False);
}

Test(components, output_component_delegation) {
    nts::OutputComponent out;
    nts::InputComponent in(nts::Tristate::True);

    // On lie l'output à l'input
    out.setLink(1, in, 1);

    // L'output doit renvoyer la valeur de l'input
    cr_assert_eq(out.compute(1), nts::Tristate::True);

    // Si on change l'input, l'output doit suivre
    in.setValue(nts::Tristate::False);
    cr_assert_eq(out.compute(1), nts::Tristate::False);
}
