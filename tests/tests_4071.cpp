/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4071
*/

#include <criterion/criterion.h>
#include "4071Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4071_or_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4071 comp;

	link_input(comp, 12, in_true);
	link_input(comp, 13, in_false);
	cr_assert_eq(comp.compute(11), nts::Tristate::True);
}

Test(components, chip_4071_full_logic) {
    nts::Component4071 comp;
    nts::InputComponent in1;
    nts::InputComponent in2;

    link_input(comp, 1, in1);
    link_input(comp, 2, in2);

    // False | False = False
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    // False | True = True
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // True | True = True
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);
}

Test(components, chip_4071_tristate) {
    nts::Component4071 comp;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_undef(nts::Tristate::Undefined);
    nts::InputComponent in_false(nts::Tristate::False);

    // True | Undefined = True
    link_input(comp, 1, in_true);
    link_input(comp, 2, in_undef);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);

    // False | Undefined = Undefined
    link_input(comp, 1, in_false);
    cr_assert_eq(comp.compute(3), nts::Tristate::Undefined);
}

Test(components, chip_4071_gate_3) {
    nts::Component4071 comp;
    nts::InputComponent in1(nts::Tristate::False);
    nts::InputComponent in2(nts::Tristate::False);

    link_input(comp, 8, in1);
    link_input(comp, 9, in2);

    // Initialement False
    cr_assert_eq(comp.compute(10), nts::Tristate::False);

    // On passe une entrée à True
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(10), nts::Tristate::True);
}

Test(components, chip_4071_isolation) {
    nts::Component4071 comp;
    nts::InputComponent in_p1(nts::Tristate::True);
    nts::InputComponent in_p2(nts::Tristate::False);

    // Porte 1 (1, 2 -> 3)
    link_input(comp, 1, in_p1);
    link_input(comp, 2, in_p1);
    
    // Porte 2 (5, 6 -> 4)
    link_input(comp, 5, in_p2);
    link_input(comp, 6, in_p2);

    cr_assert_eq(comp.compute(3), nts::Tristate::True);
    cr_assert_eq(comp.compute(4), nts::Tristate::False);
}
