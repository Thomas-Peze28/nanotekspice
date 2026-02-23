/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4008
*/

#include <criterion/criterion.h>
#include "4008Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4008_basic_addition) {
    nts::Component4008 comp;
    nts::InputComponent a1(nts::Tristate::True);  // A0 (Pin 7)
    nts::InputComponent b1(nts::Tristate::True);  // B0 (Pin 6)
    nts::InputComponent cin(nts::Tristate::False); // Carry In (Pin 9)

    link_input(comp, 7, a1);
    link_input(comp, 6, b1);
    link_input(comp, 9, cin);

    // 1 + 1 + 0 = 2 (Binaire: S0=0, S1=1)
    cr_assert_eq(comp.compute(10), nts::Tristate::False); // S0 (Pin 10)
    cr_assert_eq(comp.compute(11), nts::Tristate::True);  // S1 (Pin 11)
}

Test(components, chip_4008_carry_in) {
    nts::Component4008 comp;
    nts::InputComponent a1(nts::Tristate::True);
    nts::InputComponent b1(nts::Tristate::False);
    nts::InputComponent cin(nts::Tristate::True);

    link_input(comp, 7, a1);
    link_input(comp, 6, b1);
    link_input(comp, 9, cin);

    // 1 + 0 + 1 (Cin) = 2 (S0=0, S1=1)
    cr_assert_eq(comp.compute(10), nts::Tristate::False);
    cr_assert_eq(comp.compute(11), nts::Tristate::True);
}

Test(components, chip_4008_overflow) {
    nts::Component4008 comp;
    nts::InputComponent vcc(nts::Tristate::True);
    nts::InputComponent gnd(nts::Tristate::False);

    // A = 1111 (Pins 7, 5, 3, 1)
    link_input(comp, 7, vcc); link_input(comp, 5, vcc);
    link_input(comp, 3, vcc); link_input(comp, 1, vcc);
    // B = 0001 (Pins 6, 4, 2, 15)
    link_input(comp, 6, vcc); link_input(comp, 4, gnd);
    link_input(comp, 2, gnd); link_input(comp, 15, gnd);
    // Cin = 0
    link_input(comp, 9, gnd);

    // Somme S0, S1, S2, S3 doivent être 0
    cr_assert_eq(comp.compute(10), nts::Tristate::False);
    cr_assert_eq(comp.compute(11), nts::Tristate::False);
    cr_assert_eq(comp.compute(12), nts::Tristate::False);
    cr_assert_eq(comp.compute(13), nts::Tristate::False);
    
    // Carry Out (Pin 14) doit être 1
    cr_assert_eq(comp.compute(14), nts::Tristate::True);
}

Test(components, chip_4008_tristate_propagation) {
    nts::Component4008 comp;
    nts::InputComponent in_undef(nts::Tristate::Undefined);
    nts::InputComponent in_true(nts::Tristate::True);

    link_input(comp, 7, in_undef); // A0 undef
    link_input(comp, 6, in_true);  // B0 true
    link_input(comp, 9, in_true);  // Cin true

    // Undefined + 1 + 1 = résultat indéterminé pour S0 et la retenue vers S1
    cr_assert_eq(comp.compute(10), nts::Tristate::Undefined);
    cr_assert_eq(comp.compute(11), nts::Tristate::Undefined);
}
