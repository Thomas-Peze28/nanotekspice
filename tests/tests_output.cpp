/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_output
*/

#include <criterion/criterion.h>
#include "OutputComponent.hpp"
#include "NotComponent.hpp"
#include "InputComponent.hpp"

Test(components, output_component_reflects_link) {
	nts::InputComponent input(nts::Tristate::True);
	nts::OutputComponent output;

	output.setLink(1, input, 1);
	cr_assert_eq(output.compute(1), nts::Tristate::True);
	cr_assert_eq(output.compute(2), nts::Tristate::Undefined);
}

Test(components, output_component_dynamic_update) {
    nts::InputComponent input(nts::Tristate::False);
    nts::OutputComponent output;

    output.setLink(1, input, 1);
    
    // Initialement False
    cr_assert_eq(output.compute(1), nts::Tristate::False);

    // On change l'entrée, l'output doit suivre immédiatement
    input.setValue(nts::Tristate::True);
    cr_assert_eq(output.compute(1), nts::Tristate::True);

    // Passage en Undefined
    input.setValue(nts::Tristate::Undefined);
    cr_assert_eq(output.compute(1), nts::Tristate::Undefined);
}

Test(components, output_component_no_link) {
    nts::OutputComponent output;

    // Calculer sur une pin non liée
    cr_assert_eq(output.compute(1), nts::Tristate::Undefined);
}

Test(components, output_integration_with_gate) {
    nts::InputComponent in(nts::Tristate::True);
    nts::NotComponent not_gate;
    nts::OutputComponent out;

    // Liaison : Input (1) -> Not (1) | Not (2) -> Output (1)
    not_gate.setLink(1, in, 1);
    out.setLink(1, not_gate, 2);

    // NOT True = False. L'output doit donc être False.
    cr_assert_eq(out.compute(1), nts::Tristate::False);
}
