/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_clock
*/

#include <criterion/criterion.h>
#include "ClockComponent.hpp"

Test(components, clock_component_value) {
	nts::ClockComponent clock;

	clock.setValue(nts::Tristate::True);
	cr_assert_eq(clock.compute(1), nts::Tristate::True);
	cr_assert_eq(clock.compute(2), nts::Tristate::Undefined);
}

Test(components, clock_tick_behavior) {
    nts::ClockComponent clock(nts::Tristate::True);

    cr_assert_eq(clock.compute(1), nts::Tristate::True);

    // Après un simulate, l'état doit s'inverser
    clock.simulate(0);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);

    // Nouveau simulate, retour à l'état initial
    clock.simulate(1);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
}

Test(components, clock_set_value) {
    nts::ClockComponent clock(nts::Tristate::Undefined);

    // On force à False
    clock.setValue(nts::Tristate::False);
    cr_assert_eq(clock.compute(1), nts::Tristate::False);

    // Le simulate d'un False doit donner un True
    clock.simulate(0);
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
}

Test(components, clock_undefined_simulate) {
    nts::ClockComponent clock(nts::Tristate::Undefined);

    cr_assert_eq(clock.compute(1), nts::Tristate::Undefined);
    
    clock.simulate(0);
    cr_assert_eq(clock.compute(1), nts::Tristate::Undefined);
}

Test(components, clock_invalid_pin) {
    nts::ClockComponent clock(nts::Tristate::True);

    // La pin 1 est la seule pin de sortie valide pour un composant Clock
    cr_assert_eq(clock.compute(1), nts::Tristate::True);
    
    // Selon ton implémentation, compute(2) doit renvoyer Undefined ou throw
    cr_assert_eq(clock.compute(2), nts::Tristate::Undefined);
}
