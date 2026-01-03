/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:07:43 by phillymilly       #+#    #+#             */
/*   Updated: 2026/01/03 18:51:33 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*                              Canonical Form                                */
/* ************************************************************************** */
PmergeMe::PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &copy) { (void)(copy); };

PmergeMe &PmergeMe::operator=(const PmergeMe &copy) {
	if (this == &copy) {
		return *this; 
    }
    return *this;
};

PmergeMe::~PmergeMe(){};


/* ************************************************************************** */
/*                                 Parsing                                    */
/* ************************************************************************** */
void PmergeMe::parse(std::string numbers)
{
	if (numbers.find_first_not_of("0123456789 ") != std::string::npos)
		throw std::runtime_error("Error!");

	std::stringstream ss(numbers);
	long num;
	while (ss >> num)
	{
		if (num < 1 || num > INT_MAX)
			throw std::runtime_error("Error: number is out of range.");
		_vec_pend.push_back(static_cast<int>(num));
	}
	if (_vec_pend.size() < 2)
		throw std::runtime_error("Error: not enough numbers to sort.");
	if (hasDuplicates())
		throw std::runtime_error("Error: has duplicates.");
	
	std::cout << "Before:\t" << std::ends;
	for (std::vector<int>::iterator it = _vec_pend.begin(); it != _vec_pend.end(); it++)
		std::cout << *it << ' ' << std::ends;
	std::cout << '\n';

	if (_vec_pend.size() % 2 != 0)
	{
		_vec_nums.push_back(std::make_pair(0, _vec_pend.back()));
		_deq_nums.push_back(std::make_pair(0, _vec_pend.back()));
		_vec_pend.pop_back();
	}
	for (std::vector<int>::iterator it = _vec_pend.begin(); it != _vec_pend.end(); it +=2)
	{
		_vec_nums.push_back(std::make_pair(*it, *(it + 1)));
		_deq_nums.push_back(std::make_pair(*it, *(it + 1)));
	}
	_vec_pend.clear();
}


/* ************************************************************************** */
/*                                  Vector                                    */
/* ************************************************************************** */
void PmergeMe::normalizeVecPairs()
{
	for (std::vector<std::pair<int, int> >::iterator it = _vec_nums.begin(); it != _vec_nums.end(); it++)
	{
		if (it->second < it->first)
			std::swap(it->first, it->second);
	}
}

void PmergeMe::mergeSortVec(int start, int end)
{
	if (start < end)
	{
		int mid = start + (end - start) / 2;
		mergeSortVec(start, mid);
		mergeSortVec(mid + 1, end);
		mergeVec(start, mid, end);
	}
}

void PmergeMe::mergeVec(int start, int mid, int end)
{
	int left_size = mid - start + 1;
	int right_size = end - mid;

	std::vector<std::pair<int, int> > left(left_size), right(right_size);

	for (int i = 0; i < left_size; ++i)
		left[i] = _vec_nums[start + i];
	for (int i = 0; i < right_size; ++i)
		right[i] = _vec_nums[mid + 1 + i];
	
	int l = 0, r = 0, i = start;
	while (l < left_size && r < right_size)
	{
		if (left[l].second < right[r].second)
			_vec_nums[i] = left[l++];
		else
			_vec_nums[i] = right[r++];
		++i;
	}
	while (l < left_size)
		_vec_nums[i++] = left[l++];
	while (r < right_size)
		_vec_nums[i++] = right[r++];
}

void PmergeMe::insertSortVec()
{
	for (size_t i = 0; i < _vec_nums.size(); ++i)
	{
		_vec_main.push_back(_vec_nums[i].second);
		_vec_pend.push_back(_vec_nums[i].first);
	}

	int val = _vec_pend[0];
	std::vector<int>::iterator pos = std::lower_bound(_vec_main.begin(), _vec_main.end(), val);
	_vec_main.insert(pos, val);

	size_t inserted = 1, i = 2;
	while (inserted < _vec_pend.size())
	{
		size_t cur = jacobsthal(i), prev = jacobsthal(i - 1);

		if (cur > _vec_pend.size())
			cur = _vec_pend.size();
		
		for (size_t j = cur; j > prev && inserted < _vec_pend.size(); --j)
		{
			int val = _vec_pend[j - 1];
			std::vector<int>::iterator pos = std::lower_bound(_vec_main.begin(), _vec_main.end(), val);
			_vec_main.insert(pos, val);
			++inserted;
		}
		++i;
	}
}

void PmergeMe::sortVec()
{
	clock_t	start = clock();
	
	normalizeVecPairs();
	mergeSortVec(0, _vec_nums.size() - 1);
	insertSortVec();

	if (_vec_main.front() == 0)
		_vec_main.erase(_vec_main.begin());
	
	clock_t end = clock();
	
	std::cout << "After:\t" << std::ends;
	for (std::vector<int>::iterator it = _vec_main.begin(); it != _vec_main.end(); it++)
		std::cout << *it << ' ' << std::ends;
	std::cout << '\n';

	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << _vec_main.size() << " elements with std::[vector] : " << time << " us" << '\n'; 
}


/* ************************************************************************** */
/*                                  Deque                                     */
/* ************************************************************************** */
void PmergeMe::normalizeDeqPairs()
{
	for (std::deque<std::pair<int, int> >::iterator it = _deq_nums.begin(); it != _deq_nums.end(); it++)
	{
		if (it->second < it->first)
			std::swap(it->first, it->second);
	}
}

void PmergeMe::mergeSortDeq(int start, int end)
{
	if (start < end)
	{
		int mid = start + (end - start) / 2;
		mergeSortDeq(start, mid);
		mergeSortDeq(mid + 1, end);
		mergeDeq(start, mid, end);
	}
}

void PmergeMe::mergeDeq(int start, int mid, int end)
{
	int left_size = mid - start + 1;
	int right_size = end - mid;

	std::deque<std::pair<int, int> > left(left_size), right(right_size);

	for (int i = 0; i < left_size; ++i)
		left[i] = _deq_nums[start + i];
	for (int i = 0; i < right_size; ++i)
		right[i] = _deq_nums[mid + 1 + i];
	
	int l = 0, r = 0, i = start;
	while (l < left_size && r < right_size)
	{
		if (left[l].second < right[r].second)
			_deq_nums[i] = left[l++];
		else
			_deq_nums[i] = right[r++];
		++i;
	}
	while (l < left_size)
		_deq_nums[i++] = left[l++];
	while (r < right_size)
		_deq_nums[i++] = right[r++];
}

void PmergeMe::insertSortDeq()
{
	for (size_t i = 0; i < _deq_nums.size(); ++i)
	{
		_deq_main.push_back(_deq_nums[i].second);
		_deq_pend.push_back(_deq_nums[i].first);
	}

	int val = _deq_pend[0];
	std::deque<int>::iterator pos = std::lower_bound(_deq_main.begin(), _deq_main.end(), val);
	_deq_main.insert(pos, val);

	size_t inserted = 1, i = 2;
	while (inserted < _deq_pend.size())
	{
		size_t cur = jacobsthal(i), prev = jacobsthal(i - 1);

		if (cur > _deq_pend.size())
			cur = _deq_pend.size();
		
		for (size_t j = cur; j > prev && inserted < _deq_pend.size(); --j)
		{
			int val = _deq_pend[j - 1];
			std::deque<int>::iterator pos = std::lower_bound(_deq_main.begin(), _deq_main.end(), val);
			_deq_main.insert(pos, val);
			++inserted;
		}
		++i;
	}
}

void PmergeMe::sortDeq()
{
	clock_t	start = clock();
	
	normalizeDeqPairs();
	mergeSortDeq(0, _deq_nums.size() - 1);
	insertSortDeq();

	if (_deq_main.front() == 0)
		_deq_main.erase(_deq_main.begin());
	
	clock_t end = clock();

	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << _deq_main.size() << " elements with std::[deque] : " << time << " us" << '\n'; 
}


/* ************************************************************************** */
/*                             Helper-functions                               */
/* ************************************************************************** */
size_t jacobsthal(size_t n)
{
	if (n == 0 || n == 1) 
		return (n);

	size_t a = 0, b = 1, c;
	for (size_t i = 2; i <= n; ++i)
	{
		c = b + 2 * a;
		a = b;
		b = c;
	}
	return (b);
}

bool PmergeMe::hasDuplicates()
{
	for (std::vector<int>::iterator it = _vec_pend.begin(); it != _vec_pend.end(); it++)
	{
		int elem_count = std::count(_vec_pend.begin(), _vec_pend.end(), *it);
		if (elem_count > 1)
			return (true);
	}
	return (false);
}