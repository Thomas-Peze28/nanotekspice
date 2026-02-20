/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_and
*/

#include <criterion/criterion.h>
#include "AndComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, and_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::AndComponent and_comp;

	link_input(and_comp, 1, in_true);
	link_input(and_comp, 2, in_false);
	cr_assert_eq(and_comp.compute(3), nts::Tristate::False);
	cr_assert_eq(and_comp.compute(1), nts::Tristate::Undefined);
}

Test(components, and_logic_full) {
    nts::AndComponent and_gate;
    nts::InputComponent in1;
    nts::InputComponent in2;

    and_gate.setLink(1, in1, 1);
    and_gate.setLink(2, in2, 1);

    // False & False = False
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(and_gate.compute(3), nts::Tristate::False);

    // True & False = False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(and_gate.compute(3), nts::Tristate::False);

    // True & True = True
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(and_gate.compute(3), nts::Tristate::True);
}

Test(components, and_tristate_behavior) {
    nts::AndComponent and_gate;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // False & Undefined = False (Le False est dominant)
    and_gate.setLink(1, in_false, 1);
    and_gate.setLink(2, in_undef, 1);
    cr_assert_eq(and_gate.compute(3), nts::Tristate::False);

    // True & Undefined = Undefined
    and_gate.setLink(1, in_true, 1);
    cr_assert_eq(and_gate.compute(3), nts::Tristate::Undefined);
}

Test(components, and_unlinked_inputs) {
    nts::AndComponent and_gate;
    nts::InputComponent in_true(nts::Tristate::True);

    // On ne lie que la pin 1
    and_gate.setLink(1, in_true, 1);
    
    // La pin 2 est vide, donc la sortie 3 doit être Undefined
    cr_assert_eq(and_gate.compute(3), nts::Tristate::Undefined);
}
