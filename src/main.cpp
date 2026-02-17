#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> clean_string(const std::string& str)
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


std::vector<std::vector<std::string>> parse_file(std::string file_name)
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

int main()
{
    std::vector<std::vector<std::string>> lines = parse_file("G-OOP-400_nanotekspice/nts_single/and.nts");
    for (std::vector<std::string> line : lines) {
        for (std::string word : line)
            std::cout << word << "|";
        std::cout << std::endl;
    }
    return 0;
}
