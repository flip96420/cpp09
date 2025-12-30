/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:48:35 by phillymilly       #+#    #+#             */
/*   Updated: 2025/12/30 17:50:21 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &copy) :_numbers(copy._numbers) {}

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		this->_numbers = copy._numbers;
	return (*this);
}

RPN::~RPN(void) {}

int RPN::process(const std::string& expression)
{
	std::istringstream iss(expression);
	char token;

	while (iss >> token)
	{
		if (std::isdigit(token))
			_numbers.push(token - '0');
		else if (token == '+' || token == '-' || token == '*' || token == '/')
			processOperation(token);
		else
			throw std::runtime_error("Error: invalid character.");
	}

	if (_numbers.size() != 1)
		throw std::runtime_error("Error: unsolved operant left.");
	return (_numbers.top());
}

void RPN::processOperation(char op)
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Error: not enough numbers.");

	int b = _numbers.top();
	_numbers.pop();
	int a = _numbers.top();
	_numbers.pop();

	int result;
	if (op == '+')
		result = a + b;
	else if (op == '-')
		result = a - b;
	else if (op == '*')
		result = a * b;
	else
	{
		if (b == 0)
			throw std::runtime_error("Error: division with 0 is not popssible.");
		result = a / b;
	}
	
	_numbers.push(result);
}