/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_
#include <vector>
#include <iostream>
#include <fstream>

namespace nts {
    class Parsing {
        public:
            Parsing();
            ~Parsing();
            std::vector<std::vector<std::string>> get_chipsets() const;
            std::vector<std::vector<std::string>> get_links() const;
            void set_chipsets_links(std::vector<std::vector<std::string>> file_content);
            std::vector<std::string> clean_string(const std::string& str);
            std::vector<std::vector<std::string>> parse_file_name(std::string file_name);
            bool is_valid_file(std::string file_name);
            bool are_valid_arguments();
            bool are_valid_links();
            bool are_valid_pins(std::vector<std::string> link, int *v_1, int *v_2);

        private:
            std::vector<std::vector<std::string>> _chipsets;
            std::vector<std::vector<std::string>> _links;
    };
}

#endif /* !PARSING_HPP_ */
