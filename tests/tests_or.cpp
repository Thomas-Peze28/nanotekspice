/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_and
*/

#include <criterion/criterion.h>
#include "OrComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, or_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::OrComponent or_comp;

	link_input(or_comp, 1, in_true);
	link_input(or_comp, 2, in_false);
	cr_assert_eq(or_comp.compute(3), nts::Tristate::True);
}

Test(components, or_logic_full) {
    nts::OrComponent or_gate;
    nts::InputComponent in1;
    nts::InputComponent in2;

    or_gate.setLink(1, in1, 1);
    or_gate.setLink(2, in2, 1);

    // False | False = False
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(or_gate.compute(3), nts::Tristate::False);

    // False | True = True
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(or_gate.compute(3), nts::Tristate::True);

    // True | True = True
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(or_gate.compute(3), nts::Tristate::True);
}

Test(components, or_tristate_behavior) {
    nts::OrComponent or_gate;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // True | Undefined = True (Le True gagne)
    or_gate.setLink(1, in_true, 1);
    or_gate.setLink(2, in_undef, 1);
    cr_assert_eq(or_gate.compute(3), nts::Tristate::True);

    // False | Undefined = Undefined (On ne peut pas conclure)
    or_gate.setLink(1, in_false, 1);
    cr_assert_eq(or_gate.compute(3), nts::Tristate::Undefined);
}

Test(components, or_invalid_pins) {
    nts::OrComponent or_gate;
    nts::InputComponent in(nts::Tristate::True);

    or_gate.setLink(1, in, 1);
    
    // Pin d'entrée ou inexistante
    cr_assert_eq(or_gate.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(or_gate.compute(4), nts::Tristate::Undefined);
}

Test(components, or_invalid_pins_coverage) {
    nts::OrComponent or_gate;
    
    // Test des pins d'entrée (ne doivent pas renvoyer de valeur)
    cr_assert_eq(or_gate.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(or_gate.compute(2), nts::Tristate::Undefined);
    
    // Test d'une pin aléatoire
    cr_assert_eq(or_gate.compute(8), nts::Tristate::Undefined);
}
