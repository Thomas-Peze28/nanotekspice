/*
** EPITECH PROJECT, 2026
** project
** File description:
** 4514Component
*/

#include "4514Component.hpp"

nts::Component4514::Component4514() : _latch(-1)
{
}

/*
** @brief Compute the output of the 4514Component based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::Component4514::compute(std::size_t pin)
{
    std::size_t outputPins[16] = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    nts::Tristate strobe = getLink(1);
    
    if (strobe == nts::Tristate::True) {
        nts::Tristate in_a = getLink(2);
        nts::Tristate in_b = getLink(3);
        nts::Tristate in_c = getLink(21);
        nts::Tristate in_d = getLink(22);

        if (in_a == nts::Tristate::Undefined || in_b == nts::Tristate::Undefined || 
            in_c == nts::Tristate::Undefined || in_d == nts::Tristate::Undefined) {
            _latch = -1;
        } else {
            _latch = (in_a * 1) + (in_b * 2) + (in_c * 4) + (in_d * 8);
        }
    } else if (strobe == nts::Tristate::Undefined) {
        return nts::Tristate::Undefined;
    }

    nts::Tristate inhibit = getLink(23);
    if (inhibit == nts::Tristate::Undefined) {
        return nts::Tristate::Undefined;
    }
    if (inhibit == nts::Tristate::True) {
        return nts::Tristate::False;
    }

    if (_latch == -1) {
        return nts::Tristate::Undefined;
    }

    std::size_t active_pin = outputPins[_latch];

    if (pin == active_pin) {
        return nts::Tristate::True;
    } else {
        return nts::Tristate::False;
    }
}