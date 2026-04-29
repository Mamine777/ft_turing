/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:00:51 by mokariou          #+#    #+#             */
/*   Updated: 2026/04/21 15:49:22 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_turing.hpp"

int main(int ac, char **av) {
    
    if (ac != 2) {
            std::cerr << "Usage: " << av[0] << " <machine.json>" << std::endl;
            return 1;
    }
    try {
        Machine machine = parse_machine(av[1]);
        std::cout << "Machine '" << machine.name << "' parsed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
