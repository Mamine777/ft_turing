/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turing.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:01:26 by mokariou          #+#    #+#             */
/*   Updated: 2026/04/29 11:41:21 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TURING_HPP
# define FT_TURING_HPP
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <set>
# include <algorithm>
# include <stdexcept>
# include <fstream>
# include <sstream>
# include <cctype>
# include <cstdlib>
# include <ctime>
# include <cmath>
# include <limits>
# include <iomanip>
# include <memory>
# include <utility>
# include <functional>
# include <type_traits>
# include <iterator>
# include <numeric>
#include <algorithm>
#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

struct Transition {
    std::string read;
    std::string to_state;
    std::string write;
    std::string action;
};
struct Machine {
    std::string name;
    std::vector<std::string> alphabet;
    std::string blank;
    std::vector<std::string> states;
    std::string initial;
    std::vector<std::string> finals;
    std::map<std::string, std::vector<Transition>> transitions;
};
class TuringMachine {
    public:
        TuringMachine();
        ~TuringMachine();

};
Machine parse_machine(const std::string& filename);
void validate_machine(const Machine& m);
#endif