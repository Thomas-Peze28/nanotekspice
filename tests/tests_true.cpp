/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_true
*/

#include <criterion/criterion.h>
#include "TrueComponent.hpp"
#include "NandComponent.hpp"
#include "InputComponent.hpp"

Test(components, true_components_constant) {
	nts::TrueComponent t_comp;

	cr_assert_eq(t_comp.compute(1), nts::Tristate::True);
	cr_assert_eq(t_comp.compute(2), nts::Tristate::Undefined);
}

Test(components, true_component_immutability) {
    nts::TrueComponent t_comp;

    // La valeur initiale doit être True
    cr_assert_eq(t_comp.compute(1), nts::Tristate::True);

    // Même après un tick ou une tentative de modification, il reste True
    t_comp.simulate(0);
    cr_assert_eq(t_comp.compute(1), nts::Tristate::True);
}

Test(components, true_comp_integration) {
    nts::NandComponent nand;
    nts::TrueComponent vcc;
    nts::InputComponent in(nts::Tristate::True);

    // On fixe une entrée du NAND à True via le TrueComponent
    nand.setLink(1, vcc, 1);
    nand.setLink(2, in, 1);

    // True NAND True = False
    cr_assert_eq(nand.compute(3), nts::Tristate::False);

    // True NAND False = True
    in.setValue(nts::Tristate::False);
    cr_assert_eq(nand.compute(3), nts::Tristate::True);
}

Test(components, true_comp_invalid_pins) {
    nts::TrueComponent t_comp;

    // Test sur des pins hors mapping (VCC/GND d'un chip par ex, ou pins inexistantes)
    cr_assert_eq(t_comp.compute(0), nts::Tristate::Undefined);
    cr_assert_eq(t_comp.compute(14), nts::Tristate::Undefined);
}
