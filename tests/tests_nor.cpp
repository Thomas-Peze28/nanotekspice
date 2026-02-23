/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_nand
*/

#include <criterion/criterion.h>
#include "NorComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, nor_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::NorComponent nor_comp;

	link_input(nor_comp, 1, in_false);
	link_input(nor_comp, 2, in_false);
	cr_assert_eq(nor_comp.compute(3), nts::Tristate::True);
}

Test(components, nor_logic_full) {
    nts::NorComponent nor;
    nts::InputComponent in1;
    nts::InputComponent in2;

    nor.setLink(1, in1, 1);
    nor.setLink(2, in2, 1);

    // False NOR False = True
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(nor.compute(3), nts::Tristate::True);

    // False NOR True = False
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(nor.compute(3), nts::Tristate::False);

    // True NOR True = False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(nor.compute(3), nts::Tristate::False);
}

Test(components, nor_tristate_behavior) {
    nts::NorComponent nor;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // True NOR Undefined = False (Le True "gagne")
    nor.setLink(1, in_true, 1);
    nor.setLink(2, in_undef, 1);
    cr_assert_eq(nor.compute(3), nts::Tristate::False);

    // False NOR Undefined = Undefined
    nor.setLink(1, in_false, 1);
    cr_assert_eq(nor.compute(3), nts::Tristate::Undefined);

    // Undefined NOR Undefined = Undefined
    nor.setLink(1, in_undef, 1);
    cr_assert_eq(nor.compute(3), nts::Tristate::Undefined);
}

Test(components, nor_as_not) {
    nts::NorComponent nor;
    nts::InputComponent in(nts::Tristate::True);

    // On lie la même entrée aux pins 1 et 2
    nor.setLink(1, in, 1);
    nor.setLink(2, in, 1);

    // Input True -> Output False
    cr_assert_eq(nor.compute(3), nts::Tristate::False);

    // Input False -> Output True
    in.setValue(nts::Tristate::False);
    cr_assert_eq(nor.compute(3), nts::Tristate::True);
}

Test(components, nor_invalid_pins) {
    nts::NorComponent nor;
    
    // La pin 4 n'existe pas sur une porte NOR élémentaire
    cr_assert_any_throw(nor.compute(4));
    // Calculer sur une pin d'entrée (1 ou 2) n'a pas de sens logique
    cr_assert_any_throw(nor.compute(1));
}

Test(components, nor_invalid_pins_coverage) {
    nts::NorComponent nor_gate;
    
    // Test des pins d'entrée
    cr_assert_eq(nor_gate.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(nor_gate.compute(2), nts::Tristate::Undefined);
    
    // Test d'une pin hors mapping (ex: pin 4)
    cr_assert_eq(nor_gate.compute(4), nts::Tristate::Undefined);
}
