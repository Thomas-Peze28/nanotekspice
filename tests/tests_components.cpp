#include <criterion/criterion.h>
#include "AComponent.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "ClockComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NotComponent.hpp"
#include "NandComponent.hpp"
#include "NorComponent.hpp"
#include "4001Component.hpp"
#include "4011Component.hpp"
#include "4030Component.hpp"
#include "4069Component.hpp"
#include "4071Component.hpp"
#include "4081Component.hpp"

namespace {
	void link_input(nts::AComponent &target, std::size_t pin, nts::InputComponent &input)
	{
		target.setLink(pin, input, 1);
	}
}

Test(components, input_component_updates_on_simulate) {
	nts::InputComponent input;

	cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
	input.setValue(nts::Tristate::True);
	cr_assert_eq(input.compute(1), nts::Tristate::Undefined);
	input.simulate(0);
	cr_assert_eq(input.compute(1), nts::Tristate::True);
	cr_assert_eq(input.compute(2), nts::Tristate::Undefined);
}

Test(components, output_component_reflects_link) {
	nts::InputComponent input(nts::Tristate::True);
	nts::OutputComponent output;

	output.setLink(1, input, 1);
	cr_assert_eq(output.compute(1), nts::Tristate::True);
	cr_assert_eq(output.compute(2), nts::Tristate::Undefined);
}

Test(components, true_false_components_constant) {
	nts::TrueComponent t_comp;
	nts::FalseComponent f_comp;

	cr_assert_eq(t_comp.compute(1), nts::Tristate::True);
	cr_assert_eq(t_comp.compute(2), nts::Tristate::Undefined);
	cr_assert_eq(f_comp.compute(1), nts::Tristate::False);
	cr_assert_eq(f_comp.compute(2), nts::Tristate::Undefined);
}

Test(components, clock_component_value) {
	nts::ClockComponent clock;

	clock.setValue(nts::Tristate::True);
	cr_assert_eq(clock.compute(1), nts::Tristate::True);
	cr_assert_eq(clock.compute(2), nts::Tristate::Undefined);
}

Test(components, and_or_xor_not_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::AndComponent and_comp;
	nts::OrComponent or_comp;
	nts::XorComponent xor_comp;
	nts::NotComponent not_comp;

	link_input(and_comp, 1, in_true);
	link_input(and_comp, 2, in_false);
	cr_assert_eq(and_comp.compute(3), nts::Tristate::False);
	cr_assert_eq(and_comp.compute(1), nts::Tristate::Undefined);

	link_input(or_comp, 1, in_true);
	link_input(or_comp, 2, in_false);
	cr_assert_eq(or_comp.compute(3), nts::Tristate::True);

	link_input(xor_comp, 1, in_true);
	link_input(xor_comp, 2, in_true);
	cr_assert_eq(xor_comp.compute(3), nts::Tristate::False);

	link_input(not_comp, 1, in_true);
	cr_assert_eq(not_comp.compute(2), nts::Tristate::False);
}

Test(components, nand_nor_components) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::NandComponent nand_comp;
	nts::NorComponent nor_comp;

	link_input(nand_comp, 1, in_true);
	link_input(nand_comp, 2, in_true);
	cr_assert_eq(nand_comp.compute(3), nts::Tristate::False);

	link_input(nor_comp, 1, in_false);
	link_input(nor_comp, 2, in_false);
	cr_assert_eq(nor_comp.compute(3), nts::Tristate::True);
}

Test(components, chip_4001_nor_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4001 comp;

	link_input(comp, 1, in_true);
	link_input(comp, 2, in_false);
	cr_assert_eq(comp.compute(3), nts::Tristate::False);
	cr_assert_eq(comp.compute(14), nts::Tristate::Undefined);
}

Test(components, chip_4011_nand_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4011 comp;

	link_input(comp, 5, in_true);
	link_input(comp, 6, in_false);
	cr_assert_eq(comp.compute(4), nts::Tristate::True);
}

Test(components, chip_4030_xor_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4030 comp;

	link_input(comp, 8, in_true);
	link_input(comp, 9, in_false);
	cr_assert_eq(comp.compute(10), nts::Tristate::True);
}

Test(components, chip_4069_not_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::Component4069 comp;

	link_input(comp, 1, in_true);
	cr_assert_eq(comp.compute(2), nts::Tristate::False);
}

Test(components, chip_4071_or_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4071 comp;

	link_input(comp, 12, in_true);
	link_input(comp, 13, in_false);
	cr_assert_eq(comp.compute(11), nts::Tristate::True);
}

Test(components, chip_4081_and_outputs) {
	nts::InputComponent in_true(nts::Tristate::True);
	nts::InputComponent in_false(nts::Tristate::False);
	nts::Component4081 comp;

	link_input(comp, 1, in_true);
	link_input(comp, 2, in_false);
	cr_assert_eq(comp.compute(3), nts::Tristate::False);
}
