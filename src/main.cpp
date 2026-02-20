#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include "NanoTekSpice.hpp"

int main(int argc, char **argv)
{
    nts::NanoTekSpice nanoTekSpice;

    return nanoTekSpice.run(argc, argv);
}
