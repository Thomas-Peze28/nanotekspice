/*
** EPITECH PROJECT, 2026
** Project
** File description:
** NanoTekSpice
*/

#include "NanoTekSpice.hpp"

int nts::NanoTekSpice::run(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments : got " << argc << " args, expected 2." << std::endl;
        return 84;
    }
    if (!buildCircuit(argv[1]))
    {
        return 84;
    }
    shell();
    return 0;
}

bool nts::NanoTekSpice::buildCircuit(const std::string &file_name)
{
    if (!_parser.is_valid_file(file_name))
        return false;
    std::vector<std::vector<std::string>> file_content = _parser.parse_file_name(file_name);
    if (file_content.empty())
        return false;
    _parser.set_chipsets_links(file_content);
    if (_parser.get_chipsets().empty())
    {
        std::cout << "No chipsets in file." << std::endl;
        return false;
    }
    if (!_parser.are_valid_arguments())
        return false;

    for (const auto &chipset : _parser.get_chipsets())
    {
        std::string type = chipset[0];
        std::string name = chipset[1];

        auto component = _factory.createComponent(type);
        if (component == nullptr)
            return false;

        _circuit.addComponent(name, std::move(component));
    }

    for (const auto &link : _parser.get_links())
    {
        std::string name1 = link[0];
        std::size_t pin1 = std::stoi(link[1]);
        std::string name2 = link[2];
        std::size_t pin2 = std::stoi(link[3]);

        nts::IComponent *comp1 = _circuit.getComponent(name1);
        nts::IComponent *comp2 = _circuit.getComponent(name2);

        if (comp1 == nullptr || comp2 == nullptr)
            return false;

        comp1->setLink(pin1, *comp2, pin2);
        comp2->setLink(pin2, *comp1, pin1);
    }
    return true;
}

void nts::NanoTekSpice::shell()
{
    std::string command;
    std::size_t tick = 0;

    while (true)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, command))
            break;

        if (command == "exit") {
            return;
        } else if (command == "simulate") {
            _circuit.simulate(tick);
            tick++;
        } else if (command == "display") {
            _circuit.display(tick);
        } else if (command.find("=") != std::string::npos) {
            _circuit.assignValue(command);
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
    return;
}