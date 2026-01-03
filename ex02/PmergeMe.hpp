/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phillymilly <phillymilly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:03:59 by phillymilly       #+#    #+#             */
/*   Updated: 2026/01/03 18:35:37 by phillymilly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <limits.h>
#include <ctime>

size_t jacobsthal(size_t n);

class PmergeMe
{
	private:
		bool	hasDuplicates();

		// Vector
		std::vector<std::pair<int, int> >	_vec_nums;
		std::vector<int>					_vec_main;
		std::vector<int>					_vec_pend;
		void	normalizeVecPairs();
		void	mergeSortVec(int start, int end);
		void	mergeVec(int start, int mid, int end);
		void	insertSortVec();
		
		// Deque
		std::deque<std::pair<int, int> >	_deq_nums;
		std::deque<int>						_deq_main;
		std::deque<int>						_deq_pend;
		void	normalizeDeqPairs();
		void	mergeSortDeq(int start, int end);
		void	mergeDeq(int start, int mid, int end);
		void	insertSortDeq();
		
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &copy);
		PmergeMe(const PmergeMe &copy);
		
		void	parse(std::string numbers);
		void	sortVec();
		void	sortDeq();
};
