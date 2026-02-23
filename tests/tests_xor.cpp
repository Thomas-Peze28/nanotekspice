/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_and
*/

#include <criterion/criterion.h>
#include "XorComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, xor_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::XorComponent xor_comp;

	link_input(xor_comp, 1, in_true);
	link_input(xor_comp, 2, in_true);
	cr_assert_eq(xor_comp.compute(3), nts::Tristate::False);
}

Test(components, xor_logic_full) {
    nts::XorComponent xor_gate;
    nts::InputComponent in1;
    nts::InputComponent in2;

    xor_gate.setLink(1, in1, 1);
    xor_gate.setLink(2, in2, 1);

    // False XOR False = False
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::False);

    // False XOR True = True
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::True);

    // True XOR True = False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::False);
}

Test(components, xor_tristate_behavior) {
    nts::XorComponent xor_gate;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // True XOR Undefined = Undefined
    xor_gate.setLink(1, in_true, 1);
    xor_gate.setLink(2, in_undef, 1);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::Undefined);

    // False XOR Undefined = Undefined
    xor_gate.setLink(1, in_false, 1);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::Undefined);
}

Test(components, xor_as_buffer) {
    nts::XorComponent xor_gate;
    nts::InputComponent in_val;
    nts::InputComponent in_fixed_false(nts::Tristate::False);

    xor_gate.setLink(1, in_val, 1);
    xor_gate.setLink(2, in_fixed_false, 1);

    in_val.setValue(nts::Tristate::True);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::True);

    in_val.setValue(nts::Tristate::False);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::False);
}

Test(components, xor_as_inverter) {
    nts::XorComponent xor_gate;
    nts::InputComponent in_val;
    nts::InputComponent in_fixed_true(nts::Tristate::True);

    xor_gate.setLink(1, in_val, 1);
    xor_gate.setLink(2, in_fixed_true, 1);

    in_val.setValue(nts::Tristate::True);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::False); // True XOR True = False

    in_val.setValue(nts::Tristate::False);
    cr_assert_eq(xor_gate.compute(3), nts::Tristate::True); // False XOR True = True
}

Test(components, xor_invalid_pins_coverage) {
    nts::XorComponent xor_gate;
    
    // Test des pins d'entrée (doivent renvoyer Undefined)
    cr_assert_eq(xor_gate.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(xor_gate.compute(2), nts::Tristate::Undefined);
    
    // Test d'une pin inexistante (ex: 14)
    cr_assert_eq(xor_gate.compute(14), nts::Tristate::Undefined);
}
