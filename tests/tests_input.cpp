/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_input
*/

#include <criterion/criterion.h>
#include "InputComponent.hpp"

Test(components, input_component_updates_on_simulate) {
	nts::InputComponent input;

	cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
	input.setValue(nts::Tristate::True);
	cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
	input.simulate(0);
	cr_assert_eq(input.compute(1), nts::Tristate::True);
	cr_assert_eq(input.compute(2), nts::Tristate::Undefined);
}

Test(components, input_component_delayed_update) {
    nts::InputComponent input(nts::Tristate::False);

    // On prépare un passage à True
    input.setValue(nts::Tristate::True);
    
    // La valeur de calcul doit rester False tant qu'on n'a pas simulé
    cr_assert_eq(input.compute(1), nts::Tristate::False);
    
    input.simulate(0);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
}

Test(components, input_component_multiple_sets) {
    nts::InputComponent input(nts::Tristate::Undefined);

    input.setValue(nts::Tristate::True);
    input.setValue(nts::Tristate::False); // On change d'avis
    
    cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
    
    input.simulate(0);
    cr_assert_eq(input.compute(1), nts::Tristate::False);
}

Test(components, input_component_persistence) {
    nts::InputComponent input(nts::Tristate::True);
    
    input.simulate(0);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
    
    // Simulate sans setValue ne doit rien changer
    input.simulate(1);
    cr_assert_eq(input.compute(1), nts::Tristate::True);
}
