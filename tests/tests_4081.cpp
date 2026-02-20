/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4081
*/

#include <criterion/criterion.h>
#include "AComponent.hpp"
#include "AndComponent.hpp"
#include "4081Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4081_and_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4081 comp;

	link_input(comp, 1, in_true);
	link_input(comp, 2, in_false);
	cr_assert_eq(comp.compute(3), nts::Tristate::False);
}

Test(components, chip_4081_full_logic) {
    nts::Component4081 comp;
    nts::InputComponent in1;
    nts::InputComponent in2;

    link_input(comp, 1, in1);
    link_input(comp, 2, in2);

    // False & False = False
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    // True & False = False
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);

    // True & True = True
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(comp.compute(3), nts::Tristate::True);
}

Test(components, chip_4081_tristate) {
    nts::Component4081 comp;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_undef(nts::Tristate::Undefined);
    nts::InputComponent in_false(nts::Tristate::False);

    // True & Undefined = Undefined
    link_input(comp, 1, in_true);
    link_input(comp, 2, in_undef);
    cr_assert_eq(comp.compute(3), nts::Tristate::Undefined);

    // False & Undefined = False
    link_input(comp, 1, in_false);
    cr_assert_eq(comp.compute(3), nts::Tristate::False);
}

Test(components, chip_4081_multiple_gates) {
    nts::Component4081 comp;
    nts::InputComponent in1(nts::Tristate::True);
    nts::InputComponent in2(nts::Tristate::True);
    
    // Test de la porte 4 (Pins 12 & 13 -> Pin 11)
    link_input(comp, 12, in1);
    link_input(comp, 13, in2);
    cr_assert_eq(comp.compute(11), nts::Tristate::True);

    // On change une entrée de la porte 4, la porte 1 ne doit pas bouger (si elle était liée)
    in1.setValue(nts::Tristate::False);
    cr_assert_eq(comp.compute(11), nts::Tristate::False);
}

Test(components, chip_4081_invalid_pins) {
    nts::Component4081 comp;
    
    // Calculer sur une pin d'entrée ou VSS/VDD devrait lever une exception ou gérer l'erreur
    cr_assert_any_throw(comp.compute(1)); 
    cr_assert_any_throw(comp.compute(14)); // VDD
    cr_assert_any_throw(comp.compute(42)); // Hors limites
}
