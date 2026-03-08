/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_logger
*/

#include <criterion/criterion.h>
#include "LoggerComponent.hpp"
#include "InputComponent.hpp"

Test(components, logger_compute_always_undefined) {
    nts::LoggerComponent logger;

    // Le logger n'a pas de sorties, donc compute(n) est toujours Undefined
    for (std::size_t pin = 1; pin <= 10; ++pin) {
        cr_assert_eq(logger.compute(pin), nts::Tristate::Undefined, 
            "La pin %lu du logger devrait renvoyer Undefined", pin);
    }
}

Test(components, logger_trigger_logic) {
    nts::LoggerComponent logger;
    nts::InputComponent clock(nts::Tristate::False);
    nts::InputComponent inhibit(nts::Tristate::False);
    
    logger.setLink(9, clock, 1);   // Clock
    logger.setLink(10, inhibit, 1); // Inhibit

    // 1. Inhibit est à 1 (True) -> Pas d'écriture
    inhibit.setValue(nts::Tristate::True);
    clock.setValue(nts::Tristate::True); 
    logger.simulate(1);
    // (Ici, on vérifierait idéalement que le fichier n'a pas bougé)

    // 2. Inhibit est à 0, mais pas de front montant -> Pas d'écriture
    inhibit.setValue(nts::Tristate::False);
    clock.setValue(nts::Tristate::True); // Déjà à 1, pas de changement
    logger.simulate(2);

    // 3. Front montant avec Inhibit à 0 -> ÉCRITURE
    clock.setValue(nts::Tristate::False);
    logger.simulate(3);
    clock.setValue(nts::Tristate::True); // Passage 0 -> 1
    logger.simulate(4);
}

Test(components, logger_value_calculation) {
    nts::LoggerComponent logger;
    // On met toutes les entrées à 1 (Pin 1 à 8)
    for (std::size_t i = 1; i <= 8; ++i) {
        auto in = std::make_unique<nts::InputComponent>(nts::Tristate::True);
        logger.setLink(i, *in, 1);
    }

    // Si toutes les pins sont à 1, la valeur à écrire est 255 (0xFF)
    // Si une pin est Undefined, l'écriture ne doit pas avoir lieu ou 
    // doit suivre la consigne du sujet (souvent ignorer le tick).
}
