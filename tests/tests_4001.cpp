/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4001
*/

#include <criterion/criterion.h>
#include "4001Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4001_nor_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4001 comp;

	link_input(comp, 1, in_true);
	link_input(comp, 2, in_false);
	cr_assert_eq(comp.compute(3), nts::Tristate::False);
	cr_assert_eq(comp.compute(14), nts::Tristate::Undefined);
}
Test(components, chip_4001_full_logic) {
    nts::Component4001 comp;
    nts::InputComponent in1;
    nts::InputComponent in2;

    link_input(comp, 1, in1);
    link_input(comp, 2, in2);

    // False NOR False = True
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // True NOR False = False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    // True NOR True = False
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);
}

Test(components, chip_4001_tristate) {
    nts::Component4001 comp;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // True NOR Undefined = False
    link_input(comp, 1, in_true);
    link_input(comp, 2, in_undef);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    // False NOR Undefined = Undefined
    link_input(comp, 1, in_false);
    cr_assert_eq(comp.compute(3), nts::Tristate::Undefined);
}

Test(components, chip_4001_gate_2) {
    nts::Component4001 comp;
    nts::InputComponent in1(nts::Tristate::False);
    nts::InputComponent in2(nts::Tristate::False);

    link_input(comp, 5, in1);
    link_input(comp, 6, in2);

    // False | False -> NOR -> True
    cr_assert_eq(comp.compute(4), nts::Tristate::True);

    // On passe une entrée à True -> Output False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(4), nts::Tristate::False);
}

Test(components, chip_4001_cascade) {
    nts::Component4001 nor1;
    nts::Component4001 nor2;
    nts::InputComponent in_false(nts::Tristate::False);

    // nor1: False NOR False = True (Pin 3)
    link_input(nor1, 1, in_false);
    link_input(nor1, 2, in_false);

    // nor2: (nor1 Pin 3) NOR False => True NOR False = False
    nor2.setLink(1, nor1, 3);
    link_input(nor2, 2, in_false);

    cr_assert_eq(nor2.compute(3), nts::Tristate::False);
}
