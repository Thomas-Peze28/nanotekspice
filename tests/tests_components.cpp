/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** tests_components
*/

#include <criterion/criterion.h>
#include "AComponent.hpp"
#include "IComponent.hpp"
#include <sstream>


Test(tristate, operator_not_undefined) {
    nts::Tristate value = nts::Tristate::Undefined;
    nts::Tristate result = !value;

    cr_assert_eq(result, nts::Tristate::Undefined, 
        "L'inverse de Undefined devrait être Undefined.");
}

Test(tristate, operator_not_full_coverage) {
    // Cas True -> False
    cr_assert_eq(!nts::Tristate::True, nts::Tristate::False);

    // Cas False -> True
    cr_assert_eq(!nts::Tristate::False, nts::Tristate::True);

    // Cas Undefined -> Undefined (Ton dernier else)
    cr_assert_eq(!nts::Tristate::Undefined, nts::Tristate::Undefined);
}

Test(tristate, operator_and_undefined_cases) {
    // Cas True && Undefined = Undefined
    cr_assert_eq(nts::Tristate::True && nts::Tristate::Undefined, nts::Tristate::Undefined);

    // Cas Undefined && True = Undefined
    cr_assert_eq(nts::Tristate::Undefined && nts::Tristate::True, nts::Tristate::Undefined);

    // Cas Undefined && Undefined = Undefined
    cr_assert_eq(nts::Tristate::Undefined && nts::Tristate::Undefined, nts::Tristate::Undefined);
}

Test(tristate, operator_and_full_coverage) {
    // Branche 1 : Dominance du False (if)
    cr_assert_eq(nts::Tristate::False && nts::Tristate::True, nts::Tristate::False);
    cr_assert_eq(nts::Tristate::False && nts::Tristate::Undefined, nts::Tristate::False);

    // Branche 2 : Full True (else if)
    cr_assert_eq(nts::Tristate::True && nts::Tristate::True, nts::Tristate::True);
}

Test(tristate, operator_or_else_coverage) {
    // Cas False || Undefined = Undefined
    cr_assert_eq(nts::Tristate::False || nts::Tristate::Undefined, nts::Tristate::Undefined);

    // Cas Undefined || False = Undefined
    cr_assert_eq(nts::Tristate::Undefined || nts::Tristate::False, nts::Tristate::Undefined);

    // Cas Undefined || Undefined = Undefined
    cr_assert_eq(nts::Tristate::Undefined || nts::Tristate::Undefined, nts::Tristate::Undefined);
}

Test(tristate, operator_or_full_branches) {
    // Branche 1 : Dominance du True (if)
    cr_assert_eq(nts::Tristate::True || nts::Tristate::False, nts::Tristate::True);
    cr_assert_eq(nts::Tristate::True || nts::Tristate::Undefined, nts::Tristate::True);

    // Branche 2 : Full False (else if)
    cr_assert_eq(nts::Tristate::False || nts::Tristate::False, nts::Tristate::False);
}

Test(tristate, operator_xor_else_coverage) {
    // Cas True ^ Undefined = Undefined
    cr_assert_eq(nts::Tristate::True ^ nts::Tristate::Undefined, nts::Tristate::Undefined);

    // Cas False ^ Undefined = Undefined
    cr_assert_eq(nts::Tristate::False ^ nts::Tristate::Undefined, nts::Tristate::Undefined);

    // Cas Undefined ^ True = Undefined
    cr_assert_eq(nts::Tristate::Undefined ^ nts::Tristate::True, nts::Tristate::Undefined);

    // Cas Undefined ^ Undefined = Undefined
    cr_assert_eq(nts::Tristate::Undefined ^ nts::Tristate::Undefined, nts::Tristate::Undefined);
}

Test(tristate, operator_xor_standard_branches) {
    // Branche 1 : Différents -> True (if)
    cr_assert_eq(nts::Tristate::True ^ nts::Tristate::False, nts::Tristate::True);
    cr_assert_eq(nts::Tristate::False ^ nts::Tristate::True, nts::Tristate::True);

    // Branche 2 : Identiques -> False (else if)
    cr_assert_eq(nts::Tristate::True ^ nts::Tristate::True, nts::Tristate::False);
    cr_assert_eq(nts::Tristate::False ^ nts::Tristate::False, nts::Tristate::False);
}

Test(tristate, ostream_undefined_coverage) {
    nts::Tristate value = nts::Tristate::Undefined;
    std::stringstream ss;

    ss << value;

    cr_assert_eq(ss.str(), "U", 
        "L'affichage de Undefined est incorrect. Attendu: 'U', Obtenu: '%s'", 
        ss.str().c_str());
}

Test(tristate, ostream_full_coverage) {
    std::stringstream ss1, ss2, ss3;

    ss1 << nts::Tristate::Undefined;
    cr_assert_eq(ss1.str(), "U");

    ss2 << nts::Tristate::True;
    cr_assert_eq(ss2.str(), "1");

    ss3 << nts::Tristate::False;
    cr_assert_eq(ss3.str(), "0");
}
