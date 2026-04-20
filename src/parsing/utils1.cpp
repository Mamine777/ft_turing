/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 20:56:22 by mokariou          #+#    #+#             */
/*   Updated: 2026/04/20 10:51:46 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_turing.hpp"

static bool is_json_file(const std::string& filePath) {
    return std::filesystem::path(filePath).extension() == ".json";
}

nlohmann::json parseJsonFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    nlohmann::json json_data;
    try {
        file >> json_data;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }
    return json_data;
}
void validate_machine(const Machine& m)
{

    if (m.name.empty())
        throw std::runtime_error("Machine name is missing");

    if (m.alphabet.empty())
        throw std::runtime_error("Alphabet is missing");

    if (m.blank.empty())
        throw std::runtime_error("Blank symbol is missing");

    if (m.states.empty())
        throw std::runtime_error("States are missing");

    if (m.initial.empty())
        throw std::runtime_error("Initial state is missing");


    if (std::find(m.alphabet.begin(), m.alphabet.end(), m.blank) == m.alphabet.end())
        throw std::runtime_error("Blank symbol not in alphabet");



    if (std::find(m.states.begin(), m.states.end(), m.initial) == m.states.end())
        throw std::runtime_error("Initial state not in states list");


    for (const auto& f : m.finals)
    {
        if (std::find(m.states.begin(), m.states.end(), f) == m.states.end())
            throw std::runtime_error("Final state '" + f + "' not in states list");
    }


    for (const auto& [state, vec] : m.transitions)
    {
        // state must exist
        if (std::find(m.states.begin(), m.states.end(), state) == m.states.end())
            throw std::runtime_error("Transition defined for invalid state: " + state);

        for (const auto& t : vec)
        {
            // read symbol must exist in alphabet
            if (std::find(m.alphabet.begin(), m.alphabet.end(), t.read) == m.alphabet.end())
                throw std::runtime_error("Invalid read symbol in transition");

            // write symbol must exist in alphabet
            if (std::find(m.alphabet.begin(), m.alphabet.end(), t.write) == m.alphabet.end())
                throw std::runtime_error("Invalid write symbol in transition");

            // next state must exist
            if (std::find(m.states.begin(), m.states.end(), t.to_state) == m.states.end())
                throw std::runtime_error("Invalid to_state in transition");

            // action must be valid
            if (t.action != "LEFT" && t.action != "RIGHT")
                throw std::runtime_error("Invalid action in transition (must be LEFT or RIGHT)");
        }
    }
}
Machine parse_machine(const std::string& filename) {
    Machine machine;

    if (!is_json_file(filename)) {
        throw std::runtime_error("Invalid file type: " + filename);
    }
    try {
        nlohmann::json json_data = parseJsonFile(filename);
        machine.name = json_data.at("name").get<std::string>();
        machine.alphabet = json_data.at("alphabet").get<std::vector<std::string>>();
        machine.blank = json_data.at("blank").get<std::string>();
        machine.states = json_data.at("states").get<std::vector<std::string>>();
        machine.initial = json_data.at("initial").get<std::string>();
        machine.finals = json_data.at("finals").get<std::vector<std::string>>();
        for (const auto& [state, transitions] : json_data.at("transitions").items()) {
            for (const auto& transition : transitions) {
                machine.transitions[state].push_back({
                    transition.at("read").get<std::string>(),
                    transition.at("to_state").get<std::string>(),
                    transition.at("write").get<std::string>(),
                    transition.at("action").get<std::string>()
                });
            }
        }
        try {
            validate_machine(machine);
        } catch (const std::exception& e) {
            throw std::runtime_error("Machine validation error: " + std::string(e.what()));
        }
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Error parsing machine: " + std::string(e.what()));
    }
    return machine;
}

