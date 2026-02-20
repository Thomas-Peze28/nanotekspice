/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_and
*/

#include <criterion/criterion.h>
#include "NotComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, not_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::NotComponent not_comp;

	link_input(not_comp, 1, in_true);
	cr_assert_eq(not_comp.compute(2), nts::Tristate::False);
}

Test(components, not_logic_full) {
    nts::NotComponent not_gate;
    nts::InputComponent in;

    not_gate.setLink(1, in, 1);

    // NOT True = False
    in.setValue(nts::Tristate::True);
    cr_assert_eq(not_gate.compute(2), nts::Tristate::False);

    // NOT False = True
    in.setValue(nts::Tristate::False);
    cr_assert_eq(not_gate.compute(2), nts::Tristate::True);
}

Test(components, not_tristate_behavior) {
    nts::NotComponent not_gate;
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    not_gate.setLink(1, in_undef, 1);
    
    // NOT Undefined = Undefined
    cr_assert_eq(not_gate.compute(2), nts::Tristate::Undefined);
}

Test(components, not_double_inversion) {
    nts::NotComponent not1;
    nts::NotComponent not2;
    nts::InputComponent in(nts::Tristate::True);

    // in -> not1 -> not2
    not1.setLink(1, in, 1);
    not2.setLink(1, not1, 2);

    // NOT (NOT True) = True
    cr_assert_eq(not2.compute(2), nts::Tristate::True);

    in.setValue(nts::Tristate::False);
    // NOT (NOT False) = False
    cr_assert_eq(not2.compute(2), nts::Tristate::False);
}

Test(components, not_invalid_pins) {
    nts::NotComponent not_gate;
    nts::InputComponent in(nts::Tristate::True);

    not_gate.setLink(1, in, 1);

    // La pin 3 n'existe pas sur un NOT unitaire
    cr_assert_eq(not_gate.compute(3), nts::Tristate::Undefined);
    // Tenter de lire l'entrée renvoie Undefined ou l'état de l'entrée selon ton architecture
    cr_assert_eq(not_gate.compute(1), nts::Tristate::Undefined);
}
