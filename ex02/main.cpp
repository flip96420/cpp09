/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:04:14 by phillymilly       #+#    #+#             */
/*   Updated: 2026/01/03 18:41:02 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac <= 1) {
		std::cerr << "Usage: " << av[0] << " <sequence of numbers devided by space>" << std::endl;
		return (1);
	}
	std::stringstream ss;
    for (int i = 1; i < ac; ++i)
	{
        if (i != 1)
			ss << " ";
        ss << av[i];
    }
    std::string	numbers = ss.str();
    PmergeMe	pm;
	try
	{
		pm.parse(numbers);
		pm.sortVec();
		pm.sortDeq();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}