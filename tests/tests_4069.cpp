/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4069
*/

#include <criterion/criterion.h>
#include "4069Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4069_not_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::Component4069 comp;

	link_input(comp, 1, in_true);
	cr_assert_eq(comp.compute(2), nts::Tristate::False);
}

Test(components, chip_4069_full_logic) {
    nts::Component4069 comp;
    nts::InputComponent in;

    link_input(comp, 1, in);

    // NOT True = False
    in.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(2), nts::Tristate::False);

    // NOT False = True
    in.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(2), nts::Tristate::True);
}

Test(components, chip_4069_tristate) {
    nts::Component4069 comp;
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    link_input(comp, 1, in_undef);
    cr_assert_eq(comp.compute(2), nts::Tristate::Undefined);
}

Test(components, chip_4069_gate_6) {
    nts::Component4069 comp;
    nts::InputComponent in(nts::Tristate::True);

    // Porte 6 : Pin 13 (In) -> Pin 12 (Out)
    link_input(comp, 13, in);
    cr_assert_eq(comp.compute(12), nts::Tristate::False);

    in.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(12), nts::Tristate::True);
}

Test(components, chip_4069_isolation) {
    nts::Component4069 comp;
    nts::InputComponent in1(nts::Tristate::True);  // Devrait sortir False
    nts::InputComponent in2(nts::Tristate::False); // Devrait sortir True

    link_input(comp, 1, in1); // Porte 1
    link_input(comp, 3, in2); // Porte 2

    cr_assert_eq(comp.compute(2), nts::Tristate::False);
    cr_assert_eq(comp.compute(4), nts::Tristate::True);
}
