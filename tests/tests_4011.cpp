/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4011
*/

#include <criterion/criterion.h>
#include "4011Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4011_nand_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4011 comp;

	link_input(comp, 5, in_true);
	link_input(comp, 6, in_false);
	cr_assert_eq(comp.compute(4), nts::Tristate::True);
}

Test(components, chip_4011_full_logic) {
    nts::Component4011 comp;
    nts::InputComponent in1;
    nts::InputComponent in2;

    link_input(comp, 1, in1);
    link_input(comp, 2, in2);

    // False NAND False = True
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // True NAND False = True
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // True NAND True = False
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);
}

Test(components, chip_4011_tristate) {
    nts::Component4011 comp;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // False NAND Undefined = True
    link_input(comp, 1, in_false);
    link_input(comp, 2, in_undef);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // True NAND Undefined = Undefined
    link_input(comp, 1, in_true);
    cr_assert_eq(comp.compute(3), nts::Tristate::Undefined);
}

Test(components, chip_4011_gate_3) {
    nts::Component4011 comp;
    nts::InputComponent in1(nts::Tristate::True);
    nts::InputComponent in2(nts::Tristate::True);

    link_input(comp, 8, in1);
    link_input(comp, 9, in2);

    // True & True -> NAND -> False
    cr_assert_eq(comp.compute(10), nts::Tristate::False);

    // On change une entrée -> True
    in1.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(10), nts::Tristate::True);
}

Test(components, chip_4011_as_not) {
    nts::Component4011 comp;
    nts::InputComponent in(nts::Tristate::True);

    // On lie la même entrée sur les pins 1 et 2
    link_input(comp, 1, in);
    link_input(comp, 2, in);

    // Input True -> Output False
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    in.setValue(nts::Tristate::False);
    // Input False -> Output True
    cr_assert_eq(comp.compute(3), nts::Tristate::True);
}
