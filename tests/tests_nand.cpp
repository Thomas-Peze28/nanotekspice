/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_nand
*/

#include <criterion/criterion.h>
#include "NandComponent.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, nand_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::NandComponent nand_comp;

	link_input(nand_comp, 1, in_true);
	link_input(nand_comp, 2, in_true);
	cr_assert_eq(nand_comp.compute(3), nts::Tristate::False);
}

Test(components, nand_logic_full) {
    nts::NandComponent nand;
    nts::InputComponent in1;
    nts::InputComponent in2;

    nand.setLink(1, in1, 1);
    nand.setLink(2, in2, 1);

    // False NAND False = True
    in1.setValue(nts::Tristate::False);
    in2.setValue(nts::Tristate::False);
    cr_assert_eq(nand.compute(3), nts::Tristate::True);

    // True NAND False = True
    in1.setValue(nts::Tristate::True);
    cr_assert_eq(nand.compute(3), nts::Tristate::True);

    // True NAND True = False
    in2.setValue(nts::Tristate::True);
    cr_assert_eq(nand.compute(3), nts::Tristate::False);
}

Test(components, nand_tristate_behavior) {
    nts::NandComponent nand;
    nts::InputComponent in_true(nts::Tristate::True);
    nts::InputComponent in_false(nts::Tristate::False);
    nts::InputComponent in_undef(nts::Tristate::Undefined);

    // False NAND Undefined = True
    nand.setLink(1, in_false, 1);
    nand.setLink(2, in_undef, 1);
    cr_assert_eq(nand.compute(3), nts::Tristate::True);

    // True NAND Undefined = Undefined
    nand.setLink(1, in_true, 1);
    cr_assert_eq(nand.compute(3), nts::Tristate::Undefined);

    // Undefined NAND Undefined = Undefined
    nand.setLink(1, in_undef, 1);
    cr_assert_eq(nand.compute(3), nts::Tristate::Undefined);
}

Test(components, nand_chaining) {
    nts::NandComponent nand1;
    nts::NandComponent nand2;
    nts::InputComponent in_true(nts::Tristate::True);

    // nand1: True NAND True = False (Pin 3)
    nand1.setLink(1, in_true, 1);
    nand1.setLink(2, in_true, 1);

    // nand2: (nand1 Pin 3) NAND True => False NAND True = True
    nand2.setLink(1, nand1, 3);
    nand2.setLink(2, in_true, 1);

    cr_assert_eq(nand2.compute(3), nts::Tristate::True);
}

Test(components, nand_unlinked_pins) {
    nts::NandComponent nand;
    nts::InputComponent in_true(nts::Tristate::True);

    // On ne lie que la pin 1
    nand.setLink(1, in_true, 1);
    
    // Le calcul sur la pin 3 devrait donner Undefined car la pin 2 est vide
    cr_assert_eq(nand.compute(3), nts::Tristate::Undefined);
}

Test(components, nand_invalid_pins_coverage) {
    nts::NandComponent nand;
    
    // Test sur les pins d'entrée (ne doivent pas renvoyer de valeur logique via compute)
    cr_assert_eq(nand.compute(1), nts::Tristate::Undefined, "La pin 1 ne devrait pas être calculable.");
    cr_assert_eq(nand.compute(2), nts::Tristate::Undefined, "La pin 2 ne devrait pas être calculable.");
    
    // Test sur une pin inexistante
    cr_assert_eq(nand.compute(42), nts::Tristate::Undefined, "Une pin hors limites doit renvoyer Undefined.");
}
