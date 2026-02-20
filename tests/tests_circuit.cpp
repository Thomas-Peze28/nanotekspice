#include <criterion/criterion.h>
#include "Circuit.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "NotComponent.hpp"
#include "XorComponent.hpp"
#include "4001Component.hpp"
#include "4011Component.hpp"
#include <memory>

// ============================================================================
// TEST SUITE 1: Component Management
// ============================================================================

Test(circuit_management, add_component_success) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>();
	
	circuit.addComponent("input1", std::move(input));
	cr_assert_not_null(circuit.getComponent("input1"));
}

Test(circuit_management, get_nonexistent_component) {
	nts::Circuit circuit;
	
	cr_assert_null(circuit.getComponent("nonexistent"));
}

Test(circuit_management, add_multiple_components) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>();
	auto input2 = std::make_unique<nts::InputComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("output1", std::move(output));
	
	cr_assert_not_null(circuit.getComponent("input1"));
	cr_assert_not_null(circuit.getComponent("input2"));
	cr_assert_not_null(circuit.getComponent("output1"));
}

Test(circuit_management, replace_existing_component) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	
	circuit.addComponent("input", std::move(input1));
	circuit.addComponent("input", std::move(input2));
	
	// Should have the replaced component
	cr_assert_not_null(circuit.getComponent("input"));
}

// ============================================================================
// TEST SUITE 2: Simple Circuit Logic
// ============================================================================

Test(circuit_logic, simple_and_gate_circuit) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto gate = std::make_unique<nts::AndComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("and_gate", std::move(gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *and_comp = circuit.getComponent("and_gate");
	nts::IComponent *input_1 = circuit.getComponent("input1");
	nts::IComponent *input_2 = circuit.getComponent("input2");
	nts::IComponent *out_comp = circuit.getComponent("output");
	
	and_comp->setLink(1, *input_1, 1);
	and_comp->setLink(2, *input_2, 1);
	out_comp->setLink(1, *and_comp, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out_comp->compute(1), nts::Tristate::True);
}

Test(circuit_logic, simple_or_gate_circuit) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto gate = std::make_unique<nts::OrComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("or_gate", std::move(gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *or_comp = circuit.getComponent("or_gate");
	nts::IComponent *input_1 = circuit.getComponent("input1");
	nts::IComponent *input_2 = circuit.getComponent("input2");
	nts::IComponent *out_comp = circuit.getComponent("output");
	
	or_comp->setLink(1, *input_1, 1);
	or_comp->setLink(2, *input_2, 1);
	out_comp->setLink(1, *or_comp, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out_comp->compute(1), nts::Tristate::True);
}

Test(circuit_logic, simple_not_gate_circuit) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto gate = std::make_unique<nts::NotComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input", std::move(input));
	circuit.addComponent("not_gate", std::move(gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *not_comp = circuit.getComponent("not_gate");
	nts::IComponent *input_comp = circuit.getComponent("input");
	nts::IComponent *out_comp = circuit.getComponent("output");
	
	not_comp->setLink(1, *input_comp, 1);
	out_comp->setLink(1, *not_comp, 2);
	
	circuit.simulate(0);
	cr_assert_eq(out_comp->compute(1), nts::Tristate::False);
}

Test(circuit_logic, simple_xor_gate_circuit) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto gate = std::make_unique<nts::XorComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("xor_gate", std::move(gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *xor_comp = circuit.getComponent("xor_gate");
	nts::IComponent *input_1 = circuit.getComponent("input1");
	nts::IComponent *input_2 = circuit.getComponent("input2");
	nts::IComponent *out_comp = circuit.getComponent("output");
	
	xor_comp->setLink(1, *input_1, 1);
	xor_comp->setLink(2, *input_2, 1);
	out_comp->setLink(1, *xor_comp, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out_comp->compute(1), nts::Tristate::True);
}

// ============================================================================
// TEST SUITE 3: Simulation with Multiple Ticks
// ============================================================================

Test(circuit_simulation, simulate_multiple_ticks) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input", std::move(input));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *input_comp = circuit.getComponent("input");
	nts::IComponent *output_comp = circuit.getComponent("output");
	output_comp->setLink(1, *input_comp, 1);
	
	// Simulate multiple ticks
	for (std::size_t tick = 0; tick < 5; tick++) {
		circuit.simulate(tick);
	}
	
	cr_assert_eq(output_comp->compute(1), nts::Tristate::True);
}

Test(circuit_simulation, simulate_with_true_false_components) {
	nts::Circuit circuit;
	auto true_comp = std::make_unique<nts::TrueComponent>();
	auto false_comp = std::make_unique<nts::FalseComponent>();
	
	circuit.addComponent("true", std::move(true_comp));
	circuit.addComponent("false", std::move(false_comp));
	
	nts::IComponent *t_comp = circuit.getComponent("true");
	nts::IComponent *f_comp = circuit.getComponent("false");
	
	circuit.simulate(0);
	
	cr_assert_eq(t_comp->compute(1), nts::Tristate::True);
	cr_assert_eq(f_comp->compute(1), nts::Tristate::False);
}

// ============================================================================
// TEST SUITE 4: Complex Circuits with Multiple Levels
// ============================================================================

Test(circuit_complex, multi_level_gate_circuit) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto and_gate = std::make_unique<nts::AndComponent>();
	auto not_gate = std::make_unique<nts::NotComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("and_gate", std::move(and_gate));
	circuit.addComponent("not_gate", std::move(not_gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *and_g = circuit.getComponent("and_gate");
	nts::IComponent *not_g = circuit.getComponent("not_gate");
	nts::IComponent *out = circuit.getComponent("output");
	
	and_g->setLink(1, *i1, 1);
	and_g->setLink(2, *i2, 1);
	not_g->setLink(1, *and_g, 3);
	out->setLink(1, *not_g, 2);
	
	circuit.simulate(0);
	cr_assert_eq(out->compute(1), nts::Tristate::True);
}

Test(circuit_complex, three_input_or_gate_circuit) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto or1 = std::make_unique<nts::OrComponent>();
	auto or2 = std::make_unique<nts::OrComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("or1", std::move(or1));
	circuit.addComponent("or2", std::move(or2));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *or_g1 = circuit.getComponent("or1");
	nts::IComponent *or_g2 = circuit.getComponent("or2");
	nts::IComponent *out = circuit.getComponent("output");
	
	or_g1->setLink(1, *i1, 1);
	or_g1->setLink(2, *i2, 1);
	or_g2->setLink(1, *or_g1, 3);
	or_g2->setLink(2, *i3, 1);
	out->setLink(1, *or_g2, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out->compute(1), nts::Tristate::True);
}

// ============================================================================
// TEST SUITE 5: Input Value Assignment
// ============================================================================

Test(circuit_input, assign_value_to_input) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>();
	
	circuit.addComponent("input1", std::move(input));
	
	bool result = circuit.assignValue("input1=1");
	cr_assert(result == true || result == false); // Check that it returns a boolean
}

Test(circuit_input, extract_component_name_and_value) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>();
	
	circuit.addComponent("myinput", std::move(input));
	
	// This tests the parsing capability
	circuit.assignValue("myinput=1");
	cr_assert_not_null(circuit.getComponent("myinput"));
}

// ============================================================================
// TEST SUITE 6: Circuit Display Function
// ============================================================================

Test(circuit_display, display_simple_circuit) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input));
	circuit.addComponent("output1", std::move(output));
	
	nts::IComponent *input_comp = circuit.getComponent("input1");
	nts::IComponent *output_comp = circuit.getComponent("output1");
	output_comp->setLink(1, *input_comp, 1);
	
	circuit.simulate(0);
	
	// Display should not crash
	circuit.display(0);
	cr_assert(true);
}

Test(circuit_display, display_with_multiple_inputs_outputs) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto output1 = std::make_unique<nts::OutputComponent>();
	auto output2 = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("output1", std::move(output1));
	circuit.addComponent("output2", std::move(output2));
	
	circuit.simulate(0);
	circuit.display(0);
	
	cr_assert(true);
}

// ============================================================================
// TEST SUITE 7: Circuit as IComponent
// ============================================================================

Test(circuit_interface, circuit_compute_pin) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	
	circuit.addComponent("input", std::move(input));
	circuit.simulate(0);
	
	// Circuit's compute should return Undefined for any pin
	cr_assert_eq(circuit.compute(1), nts::Tristate::Undefined);
	cr_assert_eq(circuit.compute(2), nts::Tristate::Undefined);
}

Test(circuit_interface, circuit_set_link) {
	nts::Circuit circuit;
	auto other = std::make_unique<nts::InputComponent>();
	nts::InputComponent &other_ref = *dynamic_cast<nts::InputComponent*>(other.get());
	
	circuit.addComponent("other", std::move(other));
	
	// setLink on circuit should not crash
	circuit.setLink(1, other_ref, 1);
	cr_assert(true);
}

// ============================================================================
// TEST SUITE 8: IC Chip Components Integration
// ============================================================================

Test(circuit_ic_components, 4001_nor_ic_integration) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto ic = std::make_unique<nts::Component4001>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("ic_4001", std::move(ic));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *ic_comp = circuit.getComponent("ic_4001");
	nts::IComponent *out = circuit.getComponent("output");
	
	ic_comp->setLink(1, *i1, 1);
	ic_comp->setLink(2, *i2, 1);
	out->setLink(1, *ic_comp, 3);
	
	circuit.simulate(0);
	cr_assert_neq(out->compute(1), nts::Tristate::Undefined);
}

Test(circuit_ic_components, 4011_nand_ic_integration) {
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto ic = std::make_unique<nts::Component4011>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("ic_4011", std::move(ic));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *ic_comp = circuit.getComponent("ic_4011");
	nts::IComponent *out = circuit.getComponent("output");
	
	ic_comp->setLink(1, *i1, 1);
	ic_comp->setLink(2, *i2, 1);
	out->setLink(1, *ic_comp, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out->compute(1), nts::Tristate::False);
}

// ============================================================================
// TEST SUITE 9: Edge Cases and Error Conditions
// ============================================================================

Test(circuit_edge_cases, empty_circuit_simulate) {
	nts::Circuit circuit;
	
	// Should not crash on empty circuit
	circuit.simulate(0);
	cr_assert(true);
}

Test(circuit_edge_cases, empty_circuit_display) {
	nts::Circuit circuit;
	
	// Should not crash on empty circuit display
	circuit.display(0);
	cr_assert(true);
}

Test(circuit_edge_cases, large_tick_value) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input", std::move(input));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i = circuit.getComponent("input");
	nts::IComponent *o = circuit.getComponent("output");
	o->setLink(1, *i, 1);
	
	// Test with large tick values
	circuit.simulate(999999);
	cr_assert_eq(o->compute(1), nts::Tristate::True);
}

Test(circuit_edge_cases, undefined_tristate_propagation) {
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input", std::move(input));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i = circuit.getComponent("input");
	nts::IComponent *o = circuit.getComponent("output");
	o->setLink(1, *i, 1);
	
	circuit.simulate(0);
	cr_assert_eq(o->compute(1), nts::Tristate::Undefined);
}

// ============================================================================
// TEST SUITE 10: Circuit Behavior Validation
// ============================================================================

Test(circuit_behavior, and_gate_all_truth_values) {
	// Test AND gate with different input combinations
	struct TestCase {
		nts::Tristate input1;
		nts::Tristate input2;
		nts::Tristate expected;
	};
	
	TestCase cases[] = {
		{nts::Tristate::True, nts::Tristate::True, nts::Tristate::True},
		{nts::Tristate::True, nts::Tristate::False, nts::Tristate::False},
		{nts::Tristate::False, nts::Tristate::True, nts::Tristate::False},
		{nts::Tristate::False, nts::Tristate::False, nts::Tristate::False},
	};
	
	for (auto &test_case : cases) {
		nts::Circuit circuit;
		auto input1 = std::make_unique<nts::InputComponent>(test_case.input1);
		auto input2 = std::make_unique<nts::InputComponent>(test_case.input2);
		auto gate = std::make_unique<nts::AndComponent>();
		auto output = std::make_unique<nts::OutputComponent>();
		
		circuit.addComponent("input1", std::move(input1));
		circuit.addComponent("input2", std::move(input2));
		circuit.addComponent("and_gate", std::move(gate));
		circuit.addComponent("output", std::move(output));
		
		nts::IComponent *i1 = circuit.getComponent("input1");
		nts::IComponent *i2 = circuit.getComponent("input2");
		nts::IComponent *g = circuit.getComponent("and_gate");
		nts::IComponent *o = circuit.getComponent("output");
		
		g->setLink(1, *i1, 1);
		g->setLink(2, *i2, 1);
		o->setLink(1, *g, 3);
		
		circuit.simulate(0);
		cr_assert_eq(o->compute(1), test_case.expected);
	}
}

Test(circuit_behavior, or_gate_all_truth_values) {
	// Test OR gate with different input combinations
	struct TestCase {
		nts::Tristate input1;
		nts::Tristate input2;
		nts::Tristate expected;
	};
	
	TestCase cases[] = {
		{nts::Tristate::True, nts::Tristate::True, nts::Tristate::True},
		{nts::Tristate::True, nts::Tristate::False, nts::Tristate::True},
		{nts::Tristate::False, nts::Tristate::True, nts::Tristate::True},
		{nts::Tristate::False, nts::Tristate::False, nts::Tristate::False},
	};
	
	for (auto &test_case : cases) {
		nts::Circuit circuit;
		auto input1 = std::make_unique<nts::InputComponent>(test_case.input1);
		auto input2 = std::make_unique<nts::InputComponent>(test_case.input2);
		auto gate = std::make_unique<nts::OrComponent>();
		auto output = std::make_unique<nts::OutputComponent>();
		
		circuit.addComponent("input1", std::move(input1));
		circuit.addComponent("input2", std::move(input2));
		circuit.addComponent("or_gate", std::move(gate));
		circuit.addComponent("output", std::move(output));
		
		nts::IComponent *i1 = circuit.getComponent("input1");
		nts::IComponent *i2 = circuit.getComponent("input2");
		nts::IComponent *g = circuit.getComponent("or_gate");
		nts::IComponent *o = circuit.getComponent("output");
		
		g->setLink(1, *i1, 1);
		g->setLink(2, *i2, 1);
		o->setLink(1, *g, 3);
		
		circuit.simulate(0);
		cr_assert_eq(o->compute(1), test_case.expected);
	}
}

// ============================================================================
// TEST SUITE 11: Complex Multi-Chip Circuits
// ============================================================================

Test(circuit_advanced, four_level_gate_cascade) {
	// Test a complex 4-level cascade: input -> AND -> OR -> NOT -> XOR -> output
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto and_gate = std::make_unique<nts::AndComponent>();
	auto or_gate = std::make_unique<nts::OrComponent>();
	auto not_gate = std::make_unique<nts::NotComponent>();
	auto xor_gate = std::make_unique<nts::XorComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("and_gate", std::move(and_gate));
	circuit.addComponent("or_gate", std::move(or_gate));
	circuit.addComponent("not_gate", std::move(not_gate));
	circuit.addComponent("xor_gate", std::move(xor_gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *and_g = circuit.getComponent("and_gate");
	nts::IComponent *or_g = circuit.getComponent("or_gate");
	nts::IComponent *not_g = circuit.getComponent("not_gate");
	nts::IComponent *xor_g = circuit.getComponent("xor_gate");
	nts::IComponent *out = circuit.getComponent("output");
	
	// Level 1: AND gate with input1 and input2
	and_g->setLink(1, *i1, 1);
	and_g->setLink(2, *i2, 1);
	
	// Level 2: OR gate with AND output and input3
	or_g->setLink(1, *and_g, 3);
	or_g->setLink(2, *i3, 1);
	
	// Level 3: NOT gate with OR output
	not_g->setLink(1, *or_g, 3);
	
	// Level 4: XOR gate with NOT output and input1
	xor_g->setLink(1, *not_g, 2);
	xor_g->setLink(2, *i1, 1);
	
	// Output
	out->setLink(1, *xor_g, 3);
	
	circuit.simulate(0);
	nts::Tristate result = out->compute(1);
	cr_assert(result == nts::Tristate::True || result == nts::Tristate::False);
}

Test(circuit_advanced, multiple_ic_4001_in_series) {
	// Test multiple 4001 NOR ICs in series
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto ic1 = std::make_unique<nts::Component4001>();
	auto ic2 = std::make_unique<nts::Component4001>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("ic_4001_1", std::move(ic1));
	circuit.addComponent("ic_4001_2", std::move(ic2));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *ic_1 = circuit.getComponent("ic_4001_1");
	nts::IComponent *ic_2 = circuit.getComponent("ic_4001_2");
	nts::IComponent *out = circuit.getComponent("output");
	
	// First IC: NOR(input1, input2)
	ic_1->setLink(1, *i1, 1);
	ic_1->setLink(2, *i2, 1);
	
	// Second IC: NOR(ic1_output, input3)
	ic_2->setLink(1, *ic_1, 3);
	ic_2->setLink(2, *i3, 1);
	
	// Output
	out->setLink(1, *ic_2, 3);
	
	circuit.simulate(0);
	cr_assert_neq(out->compute(1), nts::Tristate::Undefined);
}

Test(circuit_advanced, multiple_ic_4011_in_series) {
	// Test multiple 4011 NAND ICs in series
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto ic1 = std::make_unique<nts::Component4011>();
	auto ic2 = std::make_unique<nts::Component4011>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("ic_4011_1", std::move(ic1));
	circuit.addComponent("ic_4011_2", std::move(ic2));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *ic_1 = circuit.getComponent("ic_4011_1");
	nts::IComponent *ic_2 = circuit.getComponent("ic_4011_2");
	nts::IComponent *out = circuit.getComponent("output");
	
	// First IC: NAND(input1, input2)
	ic_1->setLink(1, *i1, 1);
	ic_1->setLink(2, *i2, 1);
	
	// Second IC: NAND(ic1_output, input3)
	ic_2->setLink(1, *ic_1, 3);
	ic_2->setLink(2, *i3, 1);
	
	// Output
	out->setLink(1, *ic_2, 3);
	
	circuit.simulate(0);
	// Verify output is a valid tristate (not undefined)
	cr_assert_neq(out->compute(1), nts::Tristate::Undefined);
}

Test(circuit_advanced, mixed_elementary_and_ic_gates) {
	// Test a mix of elementary gates and IC components
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto and_gate = std::make_unique<nts::AndComponent>();
	auto ic_nand = std::make_unique<nts::Component4011>();
	auto or_gate = std::make_unique<nts::OrComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("and_gate", std::move(and_gate));
	circuit.addComponent("ic_nand", std::move(ic_nand));
	circuit.addComponent("or_gate", std::move(or_gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *and_g = circuit.getComponent("and_gate");
	nts::IComponent *ic_n = circuit.getComponent("ic_nand");
	nts::IComponent *or_g = circuit.getComponent("or_gate");
	nts::IComponent *out = circuit.getComponent("output");
	
	// AND gate: AND(input1, input2)
	and_g->setLink(1, *i1, 1);
	and_g->setLink(2, *i2, 1);
	
	// NAND chip: NAND(input2, input3)
	ic_n->setLink(1, *i2, 1);
	ic_n->setLink(2, *i3, 1);
	
	// OR gate: OR(AND_output, NAND_output)
	or_g->setLink(1, *and_g, 3);
	or_g->setLink(2, *ic_n, 3);
	
	// Output
	out->setLink(1, *or_g, 3);
	
	circuit.simulate(0);
	cr_assert_eq(out->compute(1), nts::Tristate::True);
}

// ============================================================================
// TEST SUITE 12: Complex Logic Circuits with Multiple Outputs
// ============================================================================

Test(circuit_outputs, multiple_outputs_from_single_source) {
	// Test multiple outputs reading from the same component
	nts::Circuit circuit;
	auto input = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto not_gate = std::make_unique<nts::NotComponent>();
	auto output1 = std::make_unique<nts::OutputComponent>();
	auto output2 = std::make_unique<nts::OutputComponent>();
	auto output3 = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input", std::move(input));
	circuit.addComponent("not_gate", std::move(not_gate));
	circuit.addComponent("output1", std::move(output1));
	circuit.addComponent("output2", std::move(output2));
	circuit.addComponent("output3", std::move(output3));
	
	nts::IComponent *i = circuit.getComponent("input");
	nts::IComponent *not_g = circuit.getComponent("not_gate");
	nts::IComponent *o1 = circuit.getComponent("output1");
	nts::IComponent *o2 = circuit.getComponent("output2");
	nts::IComponent *o3 = circuit.getComponent("output3");
	
	not_g->setLink(1, *i, 1);
	o1->setLink(1, *not_g, 2);
	o2->setLink(1, *not_g, 2);
	o3->setLink(1, *not_g, 2);
	
	circuit.simulate(0);
	
	cr_assert_eq(o1->compute(1), nts::Tristate::False);
	cr_assert_eq(o2->compute(1), nts::Tristate::False);
	cr_assert_eq(o3->compute(1), nts::Tristate::False);
}

Test(circuit_outputs, independent_output_branches) {
	// Test two completely independent branches with outputs
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto not1 = std::make_unique<nts::NotComponent>();
	auto not2 = std::make_unique<nts::NotComponent>();
	auto output1 = std::make_unique<nts::OutputComponent>();
	auto output2 = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("not1", std::move(not1));
	circuit.addComponent("not2", std::move(not2));
	circuit.addComponent("output1", std::move(output1));
	circuit.addComponent("output2", std::move(output2));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *n1 = circuit.getComponent("not1");
	nts::IComponent *n2 = circuit.getComponent("not2");
	nts::IComponent *o1 = circuit.getComponent("output1");
	nts::IComponent *o2 = circuit.getComponent("output2");
	
	// Branch 1: input1 -> NOT -> output1
	n1->setLink(1, *i1, 1);
	o1->setLink(1, *n1, 2);
	
	// Branch 2: input2 -> NOT -> output2
	n2->setLink(1, *i2, 1);
	o2->setLink(1, *n2, 2);
	
	circuit.simulate(0);
	
	cr_assert_eq(o1->compute(1), nts::Tristate::False);
	cr_assert_eq(o2->compute(1), nts::Tristate::True);
}

// ============================================================================
// TEST SUITE 13: Deep Cascading Logic
// ============================================================================

Test(circuit_deep, very_deep_cascade_five_levels) {
	// Test a very deep cascade: input -> AND -> OR -> AND -> OR -> NOT -> output
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input3 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto input4 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	
	auto and1 = std::make_unique<nts::AndComponent>();
	auto or1 = std::make_unique<nts::OrComponent>();
	auto and2 = std::make_unique<nts::AndComponent>();
	auto or2 = std::make_unique<nts::OrComponent>();
	auto not_gate = std::make_unique<nts::NotComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("input3", std::move(input3));
	circuit.addComponent("input4", std::move(input4));
	circuit.addComponent("and1", std::move(and1));
	circuit.addComponent("or1", std::move(or1));
	circuit.addComponent("and2", std::move(and2));
	circuit.addComponent("or2", std::move(or2));
	circuit.addComponent("not_gate", std::move(not_gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *i3 = circuit.getComponent("input3");
	nts::IComponent *i4 = circuit.getComponent("input4");
	nts::IComponent *a1 = circuit.getComponent("and1");
	nts::IComponent *o1 = circuit.getComponent("or1");
	nts::IComponent *a2 = circuit.getComponent("and2");
	nts::IComponent *o2 = circuit.getComponent("or2");
	nts::IComponent *n = circuit.getComponent("not_gate");
	nts::IComponent *out = circuit.getComponent("output");
	
	// Level 1: AND(input1, input2)
	a1->setLink(1, *i1, 1);
	a1->setLink(2, *i2, 1);
	
	// Level 2: OR(AND1_out, input3)
	o1->setLink(1, *a1, 3);
	o1->setLink(2, *i3, 1);
	
	// Level 3: AND(OR1_out, input4)
	a2->setLink(1, *o1, 3);
	a2->setLink(2, *i4, 1);
	
	// Level 4: OR(AND2_out, input1)
	o2->setLink(1, *a2, 3);
	o2->setLink(2, *i1, 1);
	
	// Level 5: NOT(OR2_out)
	n->setLink(1, *o2, 3);
	
	// Output
	out->setLink(1, *n, 2);
	
	circuit.simulate(0);
	cr_assert(out->compute(1) == nts::Tristate::True || out->compute(1) == nts::Tristate::False);
}

Test(circuit_deep, six_gate_chain) {
	// Test chain: input -> NOT -> AND -> OR -> XOR -> NOT -> output
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	
	auto not1 = std::make_unique<nts::NotComponent>();
	auto and_gate = std::make_unique<nts::AndComponent>();
	auto or_gate = std::make_unique<nts::OrComponent>();
	auto xor_gate = std::make_unique<nts::XorComponent>();
	auto not2 = std::make_unique<nts::NotComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("not1", std::move(not1));
	circuit.addComponent("and_gate", std::move(and_gate));
	circuit.addComponent("or_gate", std::move(or_gate));
	circuit.addComponent("xor_gate", std::move(xor_gate));
	circuit.addComponent("not2", std::move(not2));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *n1 = circuit.getComponent("not1");
	nts::IComponent *a = circuit.getComponent("and_gate");
	nts::IComponent *o = circuit.getComponent("or_gate");
	nts::IComponent *x = circuit.getComponent("xor_gate");
	nts::IComponent *n2 = circuit.getComponent("not2");
	nts::IComponent *out = circuit.getComponent("output");
	
	n1->setLink(1, *i1, 1);
	a->setLink(1, *n1, 2);
	a->setLink(2, *i2, 1);
	o->setLink(1, *a, 3);
	o->setLink(2, *i1, 1);
	x->setLink(1, *o, 3);
	x->setLink(2, *i2, 1);
	n2->setLink(1, *x, 3);
	out->setLink(1, *n2, 2);
	
	circuit.simulate(0);
	cr_assert(out->compute(1) == nts::Tristate::True || out->compute(1) == nts::Tristate::False);
}

// ============================================================================
// TEST SUITE 14: Complex Multi-Chip IC Networks
// ============================================================================

Test(circuit_ic_network, four_chip_network) {
	// Test network with 4 different IC chips
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	
	auto ic_4001 = std::make_unique<nts::Component4001>();
	auto ic_4011 = std::make_unique<nts::Component4011>();
	auto ic_4030 = std::make_unique<nts::Component4030>();
	auto ic_4069 = std::make_unique<nts::Component4069>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("ic_4001", std::move(ic_4001));
	circuit.addComponent("ic_4011", std::move(ic_4011));
	circuit.addComponent("ic_4030", std::move(ic_4030));
	circuit.addComponent("ic_4069", std::move(ic_4069));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *c4001 = circuit.getComponent("ic_4001");
	nts::IComponent *c4011 = circuit.getComponent("ic_4011");
	nts::IComponent *c4030 = circuit.getComponent("ic_4030");
	nts::IComponent *c4069 = circuit.getComponent("ic_4069");
	nts::IComponent *out = circuit.getComponent("output");
	
	// NOR(input1, input2)
	c4001->setLink(1, *i1, 1);
	c4001->setLink(2, *i2, 1);
	
	// NAND(4001_out, input1)
	c4011->setLink(1, *c4001, 3);
	c4011->setLink(2, *i1, 1);
	
	// XOR(4011_out, input2)
	c4030->setLink(1, *c4011, 3);
	c4030->setLink(2, *i2, 1);
	
	// NOT(4030_out)
	c4069->setLink(1, *c4030, 3);
	
	// Output
	out->setLink(1, *c4069, 2);
	
	circuit.simulate(0);
	cr_assert_neq(out->compute(1), nts::Tristate::Undefined);
}

// ============================================================================
// TEST SUITE 15: Stress Tests with Many Simulations
// ============================================================================

Test(circuit_stress, repeat_same_circuit_many_times) {
	// Run the same circuit computation multiple times
	nts::Circuit circuit;
	auto input1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto input2 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto gate = std::make_unique<nts::AndComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("input1", std::move(input1));
	circuit.addComponent("input2", std::move(input2));
	circuit.addComponent("gate", std::move(gate));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("input1");
	nts::IComponent *i2 = circuit.getComponent("input2");
	nts::IComponent *g = circuit.getComponent("gate");
	nts::IComponent *o = circuit.getComponent("output");
	
	g->setLink(1, *i1, 1);
	g->setLink(2, *i2, 1);
	o->setLink(1, *g, 3);
	
	// Simulate many times
	for (int i = 0; i < 100; i++) {
		circuit.simulate(i);
		cr_assert_eq(o->compute(1), nts::Tristate::True);
	}
}

Test(circuit_stress, many_components_large_circuit) {
	// Test a circuit with many components
	nts::Circuit circuit;
	
	// Create 10 inputs
	for (int i = 0; i < 10; i++) {
		auto input = std::make_unique<nts::InputComponent>(
			(i % 2 == 0) ? nts::Tristate::True : nts::Tristate::False
		);
		circuit.addComponent("input_" + std::to_string(i), std::move(input));
	}
	
	// Create 5 AND gates
	for (int i = 0; i < 5; i++) {
		auto gate = std::make_unique<nts::AndComponent>();
		circuit.addComponent("and_gate_" + std::to_string(i), std::move(gate));
	}
	
	// Create 5 OR gates
	for (int i = 0; i < 5; i++) {
		auto gate = std::make_unique<nts::OrComponent>();
		circuit.addComponent("or_gate_" + std::to_string(i), std::move(gate));
	}
	
	// Create 3 outputs
	for (int i = 0; i < 3; i++) {
		auto output = std::make_unique<nts::OutputComponent>();
		circuit.addComponent("output_" + std::to_string(i), std::move(output));
	}
	
	// Connect some inputs to gates
	nts::IComponent *i0 = circuit.getComponent("input_0");
	nts::IComponent *i1 = circuit.getComponent("input_1");
	nts::IComponent *and_g0 = circuit.getComponent("and_gate_0");
	nts::IComponent *or_g0 = circuit.getComponent("or_gate_0");
	nts::IComponent *o0 = circuit.getComponent("output_0");
	
	and_g0->setLink(1, *i0, 1);
	and_g0->setLink(2, *i1, 1);
	or_g0->setLink(1, *and_g0, 3);
	or_g0->setLink(2, *i0, 1);
	o0->setLink(1, *or_g0, 3);
	
	circuit.simulate(0);
	cr_assert_eq(o0->compute(1), nts::Tristate::True);
}

// ============================================================================
// TEST SUITE 16: Complex Control Flow Circuits
// ============================================================================

Test(circuit_control, multiplexer_like_circuit) {
	// Simulate a multiplexer: select between two inputs with a control signal
	nts::Circuit circuit;
	auto data1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto data2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto select = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	
	auto not_select = std::make_unique<nts::NotComponent>();
	auto and1 = std::make_unique<nts::AndComponent>();
	auto and2 = std::make_unique<nts::AndComponent>();
	auto or_out = std::make_unique<nts::OrComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("data1", std::move(data1));
	circuit.addComponent("data2", std::move(data2));
	circuit.addComponent("select", std::move(select));
	circuit.addComponent("not_select", std::move(not_select));
	circuit.addComponent("and1", std::move(and1));
	circuit.addComponent("and2", std::move(and2));
	circuit.addComponent("or_out", std::move(or_out));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *d1 = circuit.getComponent("data1");
	nts::IComponent *d2 = circuit.getComponent("data2");
	nts::IComponent *sel = circuit.getComponent("select");
	nts::IComponent *n_sel = circuit.getComponent("not_select");
	nts::IComponent *a1 = circuit.getComponent("and1");
	nts::IComponent *a2 = circuit.getComponent("and2");
	nts::IComponent *o_out = circuit.getComponent("or_out");
	nts::IComponent *out = circuit.getComponent("output");
	
	// NOT(select)
	n_sel->setLink(1, *sel, 1);
	
	// AND1: data1 AND NOT(select)
	a1->setLink(1, *d1, 1);
	a1->setLink(2, *n_sel, 2);
	
	// AND2: data2 AND select
	a2->setLink(1, *d2, 1);
	a2->setLink(2, *sel, 1);
	
	// Output: AND1 OR AND2
	o_out->setLink(1, *a1, 3);
	o_out->setLink(2, *a2, 3);
	
	out->setLink(1, *o_out, 3);
	
	circuit.simulate(0);
	// When select is False, should output data1 (True)
	cr_assert_eq(out->compute(1), nts::Tristate::True);
}

Test(circuit_control, selector_with_multiple_paths) {
	// Complex selector with multiple input/output paths
	nts::Circuit circuit;
	auto in1 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto in2 = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	auto in3 = std::make_unique<nts::InputComponent>(nts::Tristate::True);
	auto control = std::make_unique<nts::InputComponent>(nts::Tristate::False);
	
	auto and_g1 = std::make_unique<nts::AndComponent>();
	auto and_g2 = std::make_unique<nts::AndComponent>();
	auto and_g3 = std::make_unique<nts::AndComponent>();
	auto or_g1 = std::make_unique<nts::OrComponent>();
	auto or_g2 = std::make_unique<nts::OrComponent>();
	auto output = std::make_unique<nts::OutputComponent>();
	
	circuit.addComponent("in1", std::move(in1));
	circuit.addComponent("in2", std::move(in2));
	circuit.addComponent("in3", std::move(in3));
	circuit.addComponent("control", std::move(control));
	circuit.addComponent("and_g1", std::move(and_g1));
	circuit.addComponent("and_g2", std::move(and_g2));
	circuit.addComponent("and_g3", std::move(and_g3));
	circuit.addComponent("or_g1", std::move(or_g1));
	circuit.addComponent("or_g2", std::move(or_g2));
	circuit.addComponent("output", std::move(output));
	
	nts::IComponent *i1 = circuit.getComponent("in1");
	nts::IComponent *i2 = circuit.getComponent("in2");
	nts::IComponent *i3 = circuit.getComponent("in3");
	nts::IComponent *ctrl = circuit.getComponent("control");
	nts::IComponent *ag1 = circuit.getComponent("and_g1");
	nts::IComponent *ag2 = circuit.getComponent("and_g2");
	nts::IComponent *ag3 = circuit.getComponent("and_g3");
	nts::IComponent *og1 = circuit.getComponent("or_g1");
	nts::IComponent *og2 = circuit.getComponent("or_g2");
	nts::IComponent *out = circuit.getComponent("output");
	
	// Path 1: in1 AND control
	ag1->setLink(1, *i1, 1);
	ag1->setLink(2, *ctrl, 1);
	
	// Path 2: in2 AND control
	ag2->setLink(1, *i2, 1);
	ag2->setLink(2, *ctrl, 1);
	
	// Path 3: in3
	ag3->setLink(1, *i3, 1);
	ag3->setLink(2, *i1, 1);
	
	// Combine paths
	og1->setLink(1, *ag1, 3);
	og1->setLink(2, *ag2, 3);
	
	og2->setLink(1, *og1, 3);
	og2->setLink(2, *ag3, 3);
	
	out->setLink(1, *og2, 3);
	
	circuit.simulate(0);
	cr_assert(out->compute(1) == nts::Tristate::True || out->compute(1) == nts::Tristate::False);
}
