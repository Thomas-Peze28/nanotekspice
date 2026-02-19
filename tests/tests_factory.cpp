#include <criterion/criterion.h>
#include <string>
#include <vector>
#include "ComponentFactory.hpp"

namespace {
	const std::vector<std::string> kKnownTypes = {
		"input",
		"output",
		"clock",
		"true",
		"false",
		"and",
		"or",
		"xor",
		"not",
		"nand",
		"nor",
		"4001",
		"4011",
		"4030",
		"4069",
		"4071",
		"4081"
	};
}

Test(factory, find_creator_known_types) {
	nts::ComponentFactory factory;

	for (const auto &type : kKnownTypes) {
		cr_assert_eq(factory.find_creator(type), true);
	}
}

Test(factory, find_creator_unknown_type) {
	nts::ComponentFactory factory;

	cr_assert_eq(factory.find_creator("unknown"), false);
}

Test(factory, create_component_known_types) {
	nts::ComponentFactory factory;

	for (const auto &type : kKnownTypes) {
		auto component = factory.createComponent(type);
		cr_assert_neq(component.get(), nullptr);
	}
}

Test(factory, create_component_unknown_type) {
	nts::ComponentFactory factory;

	auto component = factory.createComponent("unknown");
	cr_assert_eq(component.get(), nullptr);
}

Test(factory, get_creators_contains_known_types) {
	nts::ComponentFactory factory;
	auto creators = factory.get_creators();

	for (const auto &type : kKnownTypes) {
		cr_assert_neq(creators.find(type), creators.end());
	}
}
