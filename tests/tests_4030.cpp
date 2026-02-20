/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_4030
*/

#include <criterion/criterion.h>
#include "4030Component.hpp"
#include "InputComponent.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, chip_4030_xor_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4030 comp;

	link_input(comp, 8, in_true);
	link_input(comp, 9, in_false);
	cr_assert_eq(comp.compute(10), nts::Tristate::True);
}
