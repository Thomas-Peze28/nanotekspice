/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-26
** File description:
** Parsing
*/

#include "Parsing.hpp"

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}

std::vector<std::string> Parsing::clean_string(const std::string& str)
{
    std::vector<std::string> words;
    std::string current_word;

    for (char c : str) {
        if (c == ' ' || c == '\t') {
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


std::vector<std::vector<std::string>> Parsing::parse_file_name(std::string file_name)
{
    std::ifstream file(file_name);
    std::vector<std::vector<std::string>> lines;

    if (!file.is_open())
        return lines;
    std::vector<std::string> words;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        words = clean_string(line);
        if (words[0][0] != '#')
            lines.push_back(words);
    }
    return lines;
}
