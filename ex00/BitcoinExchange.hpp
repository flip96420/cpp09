/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:17:00 by pschmunk          #+#    #+#             */
/*   Updated: 2025/12/29 23:14:07 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cctype>
#include <map>
#include <exception>

#define ERROR "Error: "
#define DATABASE_NAME "data.csv"

std::string isValidDate(std::string date);
std::string isValidValue(std::string value);

class BitcoinExchange
{
	private:
		std::map<std::string, double> _rates;
		
		double	getExchangeRate(const std::string &date) const;
		void	parseDbLine(const std::string &line);
		void	writeLine(const std::string &line);
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange& operator=(const BitcoinExchange &copy);
		~BitcoinExchange();

		void loadFile(const std::string &filename, const std::string &format);
	
	class OpenFileError : public std::exception {
		virtual const char* what() const throw() { return "Error: could not open file."; }
	};
	class EmptyFileError : public std::exception {
		virtual const char* what() const throw() { return "Error: file is empty."; }
	};
	class InvalidHeaderError : public std::exception {
		virtual const char* what() const throw() { return "Error: invalid header."; }
	};
	class InvalidFormatError : public std::exception {
		virtual const char* what() const throw() { return "Error: invalid database line format."; }
	};
	class InvalidDateError : public std::exception {
		virtual const char* what() const throw() { return "Error: invalid date format."; }
	};
	class InvalidValueError : public std::exception {
		virtual const char* what() const throw() { return "Error: invalid price in database."; }
	};
	class DateTooLowError : public std::exception {
		virtual const char* what() const throw() { return "Error: date too low"; }
	};
};
