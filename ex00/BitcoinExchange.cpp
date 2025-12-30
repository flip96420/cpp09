/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:16:57 by pschmunk          #+#    #+#             */
/*   Updated: 2025/12/29 23:21:59 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* ************************************************************************** */
/*                              Canonical Form                                */
/* ************************************************************************** */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) :_rates(copy._rates) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		this->_rates = copy._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}


/* ************************************************************************** */
/*                        Member-functions: private                           */
/* ************************************************************************** */
double BitcoinExchange::getExchangeRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _rates.upper_bound(date);
	if (it == _rates.begin())
		throw DateTooLowError();
	--it;
	return (it->second);
}

void	BitcoinExchange::parseDbLine(const std::string& line)
{
	std::string::size_type sep_pos = line.find(',');
	if (sep_pos == std::string::npos)
		throw InvalidFormatError();

	std::string date = line.substr(0, sep_pos);
	std::string price = line.substr(sep_pos + 1);

	if (!isValidDate(date).empty())
		throw InvalidDateError();
	if (!isValidValue(price).empty())
		throw InvalidValueError();

	double price_rate;
	std::stringstream ss(price);
	if (!(ss >> price_rate))
		throw InvalidValueError();

	_rates[date] = price_rate;
}

void BitcoinExchange::writeLine(const std::string &line)
{
	std::string::size_type sep_pos = line.find(" | ");
	if (sep_pos == std::string::npos)
	{
		std::cout << ERROR << "bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, sep_pos);
	std::string value = line.substr(sep_pos + 3);
	if (date.empty() || value.empty())
	{
		std::cout << ERROR << "bad input => " << line << std::endl;
		return;
	}

	std::string err_date = isValidDate(date);
	std::string err_value = isValidValue(value);
	if (!err_date.empty())
		std::cout << ERROR << err_date << std::endl;
	else if (!err_value.empty())
		std::cout << ERROR << err_value << std::endl;
	else
	{
		double rate;
		double num;
		std::stringstream ss(value);
		if (!(ss >> num))
		{
			std::cout << ERROR << "bad input => " << value << std::endl;
			return;
		}
		if (num < 0.0 || num > 1000.0)
		{
			std::cout << ERROR << "too large a number => " << value << std::endl;
			return;
		}
		
		try
		{
			rate = getExchangeRate(date);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			return;
		}
		std::cout << date << " => " << value << " = " << (num * rate) << std::endl;
	}
}


/* ************************************************************************** */
/*                        Member-functions: public                            */
/* ************************************************************************** */
void	BitcoinExchange::loadFile(const std::string &filename, const std::string &format)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw OpenFileError();

	std::string line;
	if (!std::getline(file, line))
		throw EmptyFileError();
	if (line != format)
		throw InvalidHeaderError();

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		if (filename == DATABASE_NAME)
			parseDbLine(line);
		else
			writeLine(line);
	}
	file.close();
}


/* ************************************************************************** */
/*                     Helper-functions: Date Check                           */
/* ************************************************************************** */
std::string hasCalendarFormat(int year, int month, int day)
{
	if (month < 1 || month > 12)
		return ("invalid month => " + month);

	int month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
		month_days[1] = 29;

	if (day >= 1 && day <= month_days[month - 1])
		return ("");
	return ("invalid day => " + day);
}

bool isNotInFuture(int year, int month , int day)
{
	std::time_t	now = std::time(0);
	std::tm		*local = std::localtime(&now);

	int cy = local->tm_year + 1900;
    int cm = local->tm_mon + 1;
    int cd = local->tm_mday;

    if (year != cy)
        return (year < cy);
    if (month != cm)
        return (month < cm);
    return (day <= cd);
}

std::string isValidDate(std::string date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return ("not in YYYY-MM-DD format => " + date);
	for (size_t i = 0; i < date.length(); i++)
	{
		if (i != 4 && i != 7 && !std::isdigit(date[i]))
			return ("not in YYYY-MM-DD format => " + date);
	}
	
	int year, month, day;
	char dash1, dash2;
	std::stringstream ss(date);
	ss >> year >> dash1 >> month >> dash2 >> day;

	std::string err_format = hasCalendarFormat(year, month, day);
	if (!err_format.empty())
		return (err_format);
	if (!isNotInFuture(year, month, day))
		return ("date is in the future => " + date);
	return ("");
}


/* ************************************************************************** */
/*                      Helper-functions Value Check                          */
/* ************************************************************************** */
std::string isValidValue(std::string value)
{
	if (value[0] == '-')
		return ("not a positive number => " + value);

	bool has_dot = false;
	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[i] == '.')
		{
			if (has_dot || i == 0 || i == value.length() - 1)
				return ("not a number => " + value);
			has_dot = true;
		}
		else if (!std::isdigit(value[i]))
			return ("not a number => " + value);
	}
	return ("");
}