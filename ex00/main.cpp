/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:24:51 by pschmunk          #+#    #+#             */
/*   Updated: 2025/12/29 23:12:09 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	isFile(std::string filename)
{
	if ((filename.rfind(".txt") == filename.size() - 4)
		|| (filename.rfind(".csv") == filename.size() - 4))
		return (true);
	return (false);
}

bool isValid(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr	<< "Error! Wrong number of arguments.\n";
		return (false);
	}
	std::string filename = av[1];
	if (!isFile(filename))
	{
		std::cerr	<< "Error! " << filename << " is not a file or in wrong file format.\n";
		return (false);
	}
	std::ifstream file(filename.c_str());
	if (!file.good())
	{
		std::cerr	<< "Error! " << filename << " not found.\n";
		return (false);
	}
	return (true);
}

int main(int ac, char **av)
{
	if (!isValid(ac, av))
	{
		std::cout	<< "Usage: ./btc <filename>(.csv)(.txt)\n";
		return (1);
	}
	try
	{
		BitcoinExchange exchange;
		exchange.loadFile("data.csv", "date,exchange_rate");
		exchange.loadFile(av[1], "date | value");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}