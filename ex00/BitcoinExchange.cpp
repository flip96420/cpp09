/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:16:57 by pschmunk          #+#    #+#             */
/*   Updated: 2025/10/08 17:12:04 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::list<std::string> split(const std::string &str, const std::string &delimiter)
{
    std::list<std::string> tokens;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find(delimiter, start)) != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

int is_piped(std::string line)
{
	if (line.find(" | ") != std::string::npos)
		return (1);
	return (0);
}

int is_valid_date(std::string line)
{
	std::list<std::string> date = split(line, "-");
	if (date.size() != 3)
		return (0);
	
}