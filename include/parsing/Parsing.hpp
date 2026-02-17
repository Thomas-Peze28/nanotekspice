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

class Parsing {
    public:
        Parsing();
        ~Parsing();
        std::vector<std::vector<std::string>> get_chipsets();
        std::vector<std::vector<std::string>> get_links();
        // void parse_file(std::string file_name);
        std::vector<std::string> clean_string(const std::string& str);
        std::vector<std::vector<std::string>> parse_file_name(std::string file_name);

    private:
        std::vector<std::vector<std::string>> _chipsets;
        std::vector<std::vector<std::string>> _links;
};

#endif /* !PARSING_HPP_ */
