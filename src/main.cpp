#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include "Parsing.hpp"

int main(int argc, char **argv)
{
    nts::Parsing parser;

    if (argc != 2) {
        std::cout << "Wrong number of arguments : got " << argc << " args, expected 2." << std::endl;
        return 84;
    }
    if (!parser.is_valid_file(argv[1]))
        return 84;
    std::vector<std::vector<std::string>> file_content = parser.parse_file_name(argv[1]);
    if (file_content.empty())
        return 84;
    parser.set_chipsets_links(file_content);
    if (parser.get_chipsets().empty()) {
        std::cout << "No chipsets in file." << std::endl;
        return 84;
    }
    if (!parser.are_valid_arguments())
        return 84;
    return 0;
}
