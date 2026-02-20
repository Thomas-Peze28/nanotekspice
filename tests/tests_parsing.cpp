#include <criterion/criterion.h>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "parsing/Parsing.hpp"

namespace {
    int g_temp_index = 0;

    std::string make_temp_path(const std::string &suffix)
    {
        std::filesystem::path dir = std::filesystem::temp_directory_path();
        std::string name = "nts_parsing_" + std::to_string(::getpid()) + "_" + std::to_string(g_temp_index++) + suffix;
        return (dir / name).string();
    }

    std::string write_temp_file(const std::string &content, const std::string &suffix = ".nts")
    {
        std::string path = make_temp_path(suffix);
        std::ofstream file(path);
        cr_assert(file.good());
        file << content;
        file.close();
        return path;
    }

    void remove_temp_file(const std::string &path)
    {
        std::remove(path.c_str());
    }
}

// Test(groupe_de_tests, nom_du_test)
Test(parsing, clean_string_basic) {
    nts::Parsing parser;
    std::string input = "in_1:1";
    
    std::vector<std::string> result = parser.clean_string(input);
    
    cr_assert_eq(result.size(), 2);
    
    cr_assert_str_eq(result[0].c_str(), "in_1");
    cr_assert_str_eq(result[1].c_str(), "1");
}

Test(parsing, clean_string_with_spaces) {
    nts::Parsing parser;
    std::string input = "  gate_1  :   3  ";
    
    std::vector<std::string> result = parser.clean_string(input);
    
    cr_assert_eq(result.size(), 2);
    cr_assert_str_eq(result[0].c_str(), "gate_1");
    cr_assert_str_eq(result[1].c_str(), "3");
}

Test(parsing, clean_string_multiple_tokens) {
    nts::Parsing parser;
    std::string input = "a:1 b:2";

    std::vector<std::string> result = parser.clean_string(input);

    cr_assert_eq(result.size(), 4);
    cr_assert_str_eq(result[0].c_str(), "a");
    cr_assert_str_eq(result[1].c_str(), "1");
    cr_assert_str_eq(result[2].c_str(), "b");
    cr_assert_str_eq(result[3].c_str(), "2");
}

Test(parsing, parse_file_name_basic) {
    nts::Parsing parser;
    std::string content = ".chipsets\ninput in_1\noutput out_1\n\n.links\nin_1:1 out_1:1\n# comment\n";
    std::string path = write_temp_file(content);

    std::vector<std::vector<std::string>> lines = parser.parse_file_name(path);

    remove_temp_file(path);
    cr_assert_eq(lines.size(), 5);
    cr_assert_str_eq(lines[0][0].c_str(), ".chipsets");
    cr_assert_str_eq(lines[1][0].c_str(), "input");
    cr_assert_str_eq(lines[1][1].c_str(), "in_1");
    cr_assert_str_eq(lines[3][0].c_str(), ".links");
    cr_assert_str_eq(lines[4][0].c_str(), "in_1");
    cr_assert_str_eq(lines[4][1].c_str(), "1");
    cr_assert_str_eq(lines[4][2].c_str(), "out_1");
    cr_assert_str_eq(lines[4][3].c_str(), "1");
}

Test(parsing, parse_file_name_only_comments) {
    nts::Parsing parser;
    std::string content = "# only comment\n   # still comment\n";
    std::string path = write_temp_file(content);

    std::vector<std::vector<std::string>> lines = parser.parse_file_name(path);

    remove_temp_file(path);
    cr_assert_eq(lines.size(), 0);
}

Test(parsing, parse_file_name_missing_file) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> lines = parser.parse_file_name("/tmp/nts_parsing_missing_file.nts");

    cr_assert_eq(lines.size(), 0);
}

Test(parsing, is_valid_file_extension) {
    nts::Parsing parser;

    cr_assert_eq(parser.is_valid_file("sample.nts"), true);
    cr_assert_eq(parser.is_valid_file("sample.txt"), false);
}

Test(parsing, set_chipsets_links_basic) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"},
        {".links"},
        {"in_1", "1", "out_1", "1"}
    };

    parser.set_chipsets_links(content);

    std::vector<std::vector<std::string>> chipsets = parser.get_chipsets();
    std::vector<std::vector<std::string>> links = parser.get_links();
    cr_assert_eq(chipsets.size(), 2);
    cr_assert_eq(links.size(), 1);
    cr_assert_str_eq(chipsets[0][0].c_str(), "input");
    cr_assert_str_eq(chipsets[0][1].c_str(), "in_1");
    cr_assert_str_eq(links[0][0].c_str(), "in_1");
    cr_assert_str_eq(links[0][2].c_str(), "out_1");
}

Test(parsing, set_chipsets_links_invalid_header) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {"input", "in_1"},
        {"output", "out_1"}
    };

    parser.set_chipsets_links(content);

    cr_assert_eq(parser.get_chipsets().size(), 0);
    cr_assert_eq(parser.get_links().size(), 0);
}

Test(parsing, are_valid_pins_success) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"}
    };
    parser.set_chipsets_links(content);

    int v_1 = 0;
    int v_2 = 0;
    std::vector<std::string> link = {"in_1", "1", "out_1", "2"};
    bool valid = parser.are_valid_pins(link, &v_1, &v_2);

    cr_assert_eq(valid, true);
    cr_assert_eq(v_1, 1);
    cr_assert_eq(v_2, 1);
}

Test(parsing, are_valid_links_success) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"},
        {".links"},
        {"in_1", "1", "out_1", "1"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_links(), true);
}

Test(parsing, are_valid_links_unknown_component) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {".links"},
        {"in_1", "1", "out_1", "1"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_links(), false);
}

Test(parsing, are_valid_links_invalid_pin) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"},
        {".links"},
        {"in_1", "a", "out_1", "1"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_links(), false);
}

Test(parsing, are_valid_arguments_success) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"},
        {".links"},
        {"in_1", "1", "out_1", "1"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_arguments(), true);
}

Test(parsing, are_valid_arguments_unknown_type) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"badtype", "chip_1"},
        {".links"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_arguments(), false);
}

Test(parsing, are_valid_arguments_wrong_chipset_args) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input"},
        {".links"}
    };
    parser.set_chipsets_links(content);

    cr_assert_eq(parser.are_valid_arguments(), false);
}

Test(parsing, output_operator_formats_content) {
    nts::Parsing parser;
    std::vector<std::vector<std::string>> content = {
        {".chipsets"},
        {"input", "in_1"},
        {"output", "out_1"},
        {".links"},
        {"in_1", "1", "out_1", "1"}
    };
    parser.set_chipsets_links(content);

    std::stringstream stream;
    stream << parser;
    std::string output = stream.str();

    cr_assert(output.find("Chipsets:") != std::string::npos);
    cr_assert(output.find("type: input") != std::string::npos);
    cr_assert(output.find("Links:") != std::string::npos);
    cr_assert(output.find("in_1:1 -> out_1:1") != std::string::npos);
}