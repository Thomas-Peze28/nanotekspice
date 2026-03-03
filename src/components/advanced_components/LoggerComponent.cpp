/*
** EPITECH PROJECT, 2026
** project
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"
#include <fstream>

/*
** @brief Compute the output of the LoggerComponent based on its input pins.
** @param pin The pin number to compute.
** @return The computed state of the output pin, or Undefined if the pin number is invalid
*/
nts::Tristate nts::LoggerComponent::compute(std::size_t pin)
{
   (void)pin;
    nts::Tristate inhibit = getLink(10);

    if (inhibit == nts::True || inhibit == nts::Undefined)
        return nts::False;
    
    nts::Tristate clock = getLink(9);

    if (clock == nts::False)
        return nts::False;

    nts::Tristate in_001 = getLink(1);
    nts::Tristate in_002 = getLink(2);
    nts::Tristate in_004 = getLink(3);
    nts::Tristate in_008 = getLink(4);
    nts::Tristate in_016 = getLink(5);
    nts::Tristate in_032 = getLink(6);
    nts::Tristate in_064 = getLink(7);
    nts::Tristate in_128 = getLink(8);

    if (clock == nts::Undefined || in_001 == nts::Undefined || in_002 == nts::Undefined || in_004 == nts::Undefined || in_008 == nts::Undefined || in_016 == nts::Undefined || in_032 == nts::Undefined || in_064 == nts::Undefined || in_128 == nts::Undefined)
        return nts::Undefined;

    u_int8_t value = (1 * in_001) + (2 * in_002) + (4 * in_004) + (8 * in_008) + (16 * in_016) + (32 * in_032) + (64 * in_064) + (128 * in_128);

    std::ofstream logFile("log.bin", std::ios::app);
    if (logFile.is_open()) {
        logFile << value;
        logFile.close();
    }
    return nts::True;
}

void nts::LoggerComponent::simulate(std::size_t tick)
{
    (void)tick;
    compute(0);
}