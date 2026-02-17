#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include "Parsing.hpp"

int main()
{
    Parsing parser;
    // parser.get_chipsets();
    std::vector<std::vector<std::string>> lines = parser.parse_file_name("G-OOP-400_nanotekspice/nts_single/and.nts");
    for (std::vector<std::string> line : lines) {
        std::cout << std::endl;
        for (std::string word : line)
            std::cout << word << " ";
        std::cout << std::endl;
    }
    return 0;
}
