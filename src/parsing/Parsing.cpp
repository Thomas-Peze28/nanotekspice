/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include "ComponentFactory.hpp"

nts::Parsing::Parsing()
{
}

nts::Parsing::~Parsing()
{
}

std::vector<std::vector<std::string>> nts::Parsing::get_chipsets() const
{
    return _chipsets;
}

std::vector<std::vector<std::string>> nts::Parsing::get_links() const
{
    return _links;
}

void nts::Parsing::set_chipsets_links(std::vector<std::vector<std::string>> file_content)
{
    int chip = 0;
    int lin = 0;

    if (file_content[0][0] != ".chipsets" && file_content[0][0] != ".links") {
        std::cout << "Not accepted line format in file." << std::endl;
        return;
    }
    for (std::vector<std::string> line : file_content) {
        if (line[0] == ".chipsets") {
            chip = 1;
            lin = 0;
        } else if (line[0] == ".links") {
            lin = 1;
            chip = 0;
        } else {
            if (chip == 1 && lin == 0)
                _chipsets.push_back(line);
            if (lin == 1 && chip == 0)
                _links.push_back(line);
        }
    }
    return;
}

std::vector<std::string> nts::Parsing::clean_string(const std::string& str)
{
    std::vector<std::string> words;
    std::string current_word;

    for (char c : str) {
        if (c == ' ' || c == '\t' || c == ':') {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else {
            current_word += c;
        }
    }
    if (!current_word.empty())
        words.push_back(current_word);
    return words;
}


std::vector<std::vector<std::string>> nts::Parsing::parse_file_name(std::string file_name)
{
    std::ifstream file(file_name);
    std::vector<std::vector<std::string>> lines;

    if (!file.is_open()) {
        std::cout << "Error while opening file." << std::endl;
        return lines;
    }
    std::vector<std::string> words;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        words = clean_string(line);
        if (words[0][0] != '#')
            lines.push_back(words);
    }
    if (lines.empty()) {
        std::cout << "Empty file or only commented." << std::endl;
        return lines;
    }
    return lines;
}

bool nts::Parsing::is_valid_file(std::string file_name)
{
    std::size_t len = file_name.length();

    if (file_name[len - 1] == 's' && file_name[len - 2] == 't' && file_name[len - 3] == 'n' && file_name[len - 4] == '.')
        return true;
    std::cout << "File must be a .nts file." << std::endl;
    return false;
}

bool nts::Parsing::are_valid_pins(std::vector<std::string> link, int *v_1, int *v_2)
{
    for (std::vector<std::string> chipset : _chipsets) {
        if (chipset[1] == link[0])
            *v_1 = 1;
        if (chipset[1] == link[2])
            *v_2 = 1;
        for (char c : link[1]) {
            if (!isdigit(c)) {
                std::cout << "The pin number is not a number for component " << link[0] << std::endl;
                return false;
            }
        }
        for (char c : link[3]) {
            if (!isdigit(c)) {
                std::cout << "The pin number is not a number for component " << link[2] << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool nts::Parsing::are_valid_links()
{
    int v_1 = 0;
    int v_2 = 0;

    for (std::vector<std::string> link : _links) {
        if (link.size() != 4) {
            std::cout << "Wrong number of arguments for one of the links : got " << link.size() << " args, expected 4." << std::endl;
            return false;
        }
        if (!are_valid_pins(link, &v_1, &v_2))
            return false;
        if (v_1 != 1) {
            std::cout << "Unknow component name '" << link[0] << "' for the links." << std::endl;
            return false;
        } else if (v_2 != 1) {
            std::cout << "Unknow component name '" << link[2] << "' for the links." << std::endl;
            return false;
        }
    }
    return true;
}

bool nts::Parsing::are_valid_arguments()
{
    nts::ComponentFactory c_facto;

    for (std::vector<std::string> chipset : _chipsets) {
        if (chipset.size() != 2) {
            std::cout << "Wrong number of arguments for a chipset : got " << chipset.size() << " args, expected 2." << std::endl;
            return false;
        }
        if (!c_facto.find_creator(chipset[0])) {
            std::cout << "Unknow component name '" << chipset[0] << "' for the chipsets." << std::endl;
            return false;
        }
    }
    if (!are_valid_links())
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const nts::Parsing& parsing)
{
    os << "Chipsets:" << std::endl;
    for (std::vector<std::string> chipset : parsing.get_chipsets()) {
        os << "    type: " << chipset[0] << "    name: \"" << chipset[1] << "\"" << std::endl;
    }
    os << "Links:" << std::endl;
    for (std::vector<std::string> link : parsing.get_links()) {
        os << "    " << link[0] << ":" << link[1] << " -> " << link[2] << ":" << link[3] << std::endl;
    }
    return os;
}