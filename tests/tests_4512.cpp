/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4512
*/

#include <criterion/criterion.h>
#include "4512Component.hpp"
#include "InputComponent.hpp"

Test(components, chip_4512_selection) {
    nts::Component4512 chip;
    nts::InputComponent in0(nts::Tristate::False);
    nts::InputComponent in1(nts::Tristate::True);
    nts::InputComponent addrA(nts::Tristate::False); // Bit 0
    nts::InputComponent addrB(nts::Tristate::False); // Bit 1
    nts::InputComponent addrC(nts::Tristate::False); // Bit 2
    nts::InputComponent low(nts::Tristate::False);   // Pour OE et Inh

    // Liaisons minimales
    chip.setLink(1, in0, 1);    // X0
    chip.setLink(2, in1, 1);    // X1
    chip.setLink(11, addrA, 1); // A
    chip.setLink(12, addrB, 1); // B
    chip.setLink(13, addrC, 1); // C
    chip.setLink(10, low, 1);   // Inhibit
    chip.setLink(15, low, 1);   // OE

    // Adresse 000 -> Sortie = X0 (False)
    cr_assert_eq(chip.compute(14), nts::Tristate::False);

    // Adresse 001 (A=1) -> Sortie = X1 (True)
    addrA.setValue(nts::Tristate::True);
    cr_assert_eq(chip.compute(14), nts::Tristate::True);
}

Test(components, chip_4512_inhibit) {
    nts::Component4512 chip;
    nts::InputComponent inh(nts::Tristate::True);
    nts::InputComponent oe(nts::Tristate::False);
    nts::InputComponent inX(nts::Tristate::True); // Une entrée à True

    chip.setLink(10, inh, 1);
    chip.setLink(15, oe, 1);
    // On sélectionne une entrée qui est à True
    // (par défaut adresse 000 donc X0 sur pin 1)
    chip.setLink(1, inX, 1);

    // Inhibit est True -> Z doit être False
    cr_assert_eq(chip.compute(14), nts::Tristate::False);
}

Test(components, chip_4512_oe_disabled) {
    nts::Component4512 chip;
    nts::InputComponent oe(nts::Tristate::True);
    
    chip.setLink(15, oe, 1);

    // OE est True (Disabled) -> Sortie Z est Undefined
    cr_assert_eq(chip.compute(14), nts::Tristate::Undefined);
}

Test(components, chip_4512_invalid_pins) {
    nts::Component4512 chip;

    // La pin 14 est la seule sortie. Testons la pin 1 ou 16.
    cr_assert_eq(chip.compute(1), nts::Tristate::Undefined);
    cr_assert_eq(chip.compute(16), nts::Tristate::Undefined);
}
