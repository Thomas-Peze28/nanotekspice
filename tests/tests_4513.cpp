/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4513
*/

#include <criterion/criterion.h>
#include "4513Component.hpp"
#include "InputComponent.hpp"

Test(components, chip_4513_decode_one) {
    nts::Component4513 chip;
    nts::InputComponent d0(nts::Tristate::True);  // Bit 0 (Pin 2)
    nts::InputComponent d1(nts::Tristate::False); // Bit 1 (Pin 3)
    nts::InputComponent d2(nts::Tristate::False); // Bit 2 (Pin 4)
    nts::InputComponent d3(nts::Tristate::False); // Bit 3 (Pin 7)
    nts::InputComponent le(nts::Tristate::False); // Latch Enable (Pin 1) - Transparent
    nts::InputComponent bi(nts::Tristate::True);  // Blanking Input (Pin 5) - No blanking

    chip.setLink(2, d0, 1);
    chip.setLink(3, d1, 1);
    chip.setLink(4, d2, 1);
    chip.setLink(7, d3, 1);
    chip.setLink(1, le, 1);
    chip.setLink(5, bi, 1);

    // Pour le chiffre "1" : segments b et c à 1, les autres à 0
    cr_assert_eq(chip.compute(13), nts::Tristate::False); // a
    cr_assert_eq(chip.compute(12), nts::Tristate::True);  // b
    cr_assert_eq(chip.compute(11), nts::Tristate::True);  // c
    cr_assert_eq(chip.compute(10), nts::Tristate::False); // d
}

Test(components, chip_4513_blanking) {
    nts::Component4513 chip;
    nts::InputComponent bi(nts::Tristate::False); // Blanking actif
    nts::InputComponent d0(nts::Tristate::True);  // On essaie d'afficher "1"

    chip.setLink(5, bi, 1);
    chip.setLink(2, d0, 1);

    // Tous les segments (a-g) doivent être False
    for (std::size_t pin = 9; pin <= 15; ++pin) {
        cr_assert_eq(chip.compute(pin), nts::Tristate::False);
    }
}

Test(components, chip_4513_latch_behavior) {
    nts::Component4513 chip;
    nts::InputComponent le(nts::Tristate::False);
    nts::InputComponent d0(nts::Tristate::True); // On affiche "1"
    
    chip.setLink(1, le, 1);
    chip.setLink(2, d0, 1);

    // On mémorise la valeur actuelle
    le.setValue(nts::Tristate::True);
    chip.simulate(1);
    
    // On change l'entrée pendant que c'est verrouillé
    d0.setValue(nts::Tristate::False); 
    chip.simulate(2);

    // La sortie doit toujours être "1" (segment b à True) car le latch est verrouillé
    cr_assert_eq(chip.compute(12), nts::Tristate::True);
}

Test(components, chip_4513_undefined_propagation) {
    nts::Component4513 chip;
    nts::InputComponent d0(nts::Tristate::Undefined);
    nts::InputComponent bi(nts::Tristate::True);

    chip.setLink(2, d0, 1);
    chip.setLink(5, bi, 1);

    // Une entrée Undefined rend la sortie de décodage Undefined
    cr_assert_eq(chip.compute(13), nts::Tristate::Undefined);
}
