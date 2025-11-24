/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:24:51 by pschmunk          #+#    #+#             */
/*   Updated: 2025/10/08 16:21:40 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	is_file(std::string filename, int av_pos)
{
	switch (av_pos)
	{
		case 1:
		{
			if ((filename.rfind(".txt") == filename.size() - 4)
				|| (filename.rfind(".csv") == filename.size() - 4))
				return (1);
			break;
		}
		case 2:
		{
			if (filename.rfind(".csv") == filename.size() - 4)
				return (1);
			break;
		}
		default:
			break;
	}
	return (0);
}

int is_valid(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr	<< "Error! Wrong number of arguments.\n";
		return (0);
	}
	for (int i = 1; av[i] != NULL; i++)
	{
		std::string filename = av[i];
		if (!is_file(filename, i))
		{
			std::cerr	<< "Error! " << filename << " is not a file or in wrong file format.\n";
			return (0);
		}
		std::ifstream file(av[i]);
		if (!file.good())
		{
			std::cerr	<< "Error! " << filename << " not found.\n";
			return (0);
		}
	}
	return (1);
}

int main(int ac, char **av)
{
	if (!is_valid(ac, av))
	{
		std::cout	<< "Usage: ./btc input(.csv)(.txt) source(.csv)\n";
		return (1);
	}
	return (0);
}