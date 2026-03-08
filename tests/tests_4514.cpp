/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4514
*/

#include <criterion/criterion.h>
#include "4514Component.hpp"
#include "InputComponent.hpp"

Test(components, chip_4514_select_zero) {
    nts::Component4514 chip;
    nts::InputComponent in0(nts::Tristate::False); // A (Pin 2)
    nts::InputComponent in1(nts::Tristate::False); // B (Pin 3)
    nts::InputComponent in2(nts::Tristate::False); // C (Pin 21)
    nts::InputComponent in3(nts::Tristate::False); // D (Pin 22)
    nts::InputComponent strobe(nts::Tristate::True); // EL (Pin 1) - Transparent
    nts::InputComponent inh(nts::Tristate::False);  // Inhibit (Pin 23) - Active Low

    chip.setLink(2, in0, 1);
    chip.setLink(3, in1, 1);
    chip.setLink(21, in2, 1);
    chip.setLink(22, in3, 1);
    chip.setLink(1, strobe, 1);
    chip.setLink(23, inh, 1);

    // Entrée 0 -> S0 (Pin 11) doit être True
    cr_assert_eq(chip.compute(11), nts::Tristate::True);
    
    // Une autre sortie (ex: S1 pin 9) doit être False
    cr_assert_eq(chip.compute(9), nts::Tristate::False);
}

Test(components, chip_4514_inhibit_active) {
    nts::Component4514 chip;
    nts::InputComponent inh(nts::Tristate::True);
    nts::InputComponent strobe(nts::Tristate::True);

    chip.setLink(23, inh, 1);
    chip.setLink(1, strobe, 1);

    // Peu importe l'entrée, toutes les sorties testées doivent être False
    cr_assert_eq(chip.compute(11), nts::Tristate::False); // S0
    cr_assert_eq(chip.compute(13), nts::Tristate::False); // S15
}

Test(components, chip_4514_latch_behavior) {
    nts::Component4514 chip;
    nts::InputComponent strobe(nts::Tristate::True);
    nts::InputComponent in0(nts::Tristate::True); // Entrée = 1 (S1)

    chip.setLink(1, strobe, 1);
    chip.setLink(2, in0, 1);

    // 1. On stabilise sur S1 (Pin 9)
    cr_assert_eq(chip.compute(9), nts::Tristate::True);

    // 2. On verrouille (EL = False)
    strobe.setValue(nts::Tristate::False);
    chip.simulate(1);

    // 3. On change l'entrée (Entrée = 0)
    in0.setValue(nts::Tristate::False);
    chip.simulate(2);

    // La sortie S1 (Pin 9) doit rester True car on est verrouillé !
    cr_assert_eq(chip.compute(9), nts::Tristate::True);
    // S0 (Pin 11) ne doit pas s'allumer
    cr_assert_eq(chip.compute(11), nts::Tristate::False);
}

Test(components, chip_4514_input_pins_compute) {
    nts::Component4514 chip;
    // La pin 2 est une entrée (A), compute ne doit rien donner de logique
    cr_assert_eq(chip.compute(2), nts::Tristate::Undefined);
}
