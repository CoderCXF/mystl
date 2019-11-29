#pragma once
/************************************
 *Nonmodifying Algorithm
 *foreach、count、count_if、find、find_if、search....
 ************************************/
#include "iterator.h"
namespace mystl {

	//for_each()
	template <class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function f) {
		for (; first != last; ++first) {
			f(*first);
		}
		return f;
	}

	//count & count_if

	template <class InputIterator, class T>
	typename iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, const T& value) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			if (value == *first)
				++n;
			++first;
		}
		return n;
	}

	// difference from STL

	template <class InputIterator, class T,class Predicate >
	typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& value, Predicate pre) 
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			if (pre(*last))
				++n;
			++first;
		}
		return n;
	}

	//min_element & max_element & minmax_element

	template <class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last) 
	{
		if (first == last)
			return first;
		++first;
		ForwardIterator smallest = first;
		for (; first != last; ++first) {
			if (*first < smallest) {
				smallest = first;
			}
		}
	}

	template <class ForwardIterator, class BinaryCompare >
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, BinaryCompare comp) 
	{
		if (first == last)
			return first;
		++first;
		ForwardIterator smallest = first;
		for (; first != last; ++first) {
			if (comp(*first, smallest)) {
				smallest = first;
			}
		}
	}

	template <class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last) 
	{
		if (first == last)
			return first;
		++first;
		ForwardIterator max = first;
		for (; first != last; ++first) {
			if (*first > max) {
				max = first;
			}
		}
	}

	template <class ForwardIterator, class BinaryCompare >
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, BinaryCompare comp) 
	{
		if (first == last)
			return first;
		++first;
		ForwardIterator max = first;
		for (; first != last; ++first) {
			if (comp(*first, max)) {
				max = first;
			}
		}
	}

	//minmax_element not be realized
	//because return value type is pair<>, and pair<> is not realized

	//find & find_if & find_if_not &find_end & find_first_of

	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		while (first != last) {
			if (*first == val) 
				return first;
			++first;
		}
		return last;
	}

	//find_if

	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		while (first != last) {
			if (pred(*first)) return first;
			++first;
		}
		return last;
	}

	//find_if_not

	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
	{
		while (first != last) {
			if (!pred(*first)) return first;
			++first;
		}
		return last;
	}

	//find_end

	template <class ForwardIterator1, class ForwardIterator2 >
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		                      ForwardIterator2 first2, ForwardIterator2 last2) 
	{
		if (first2 == last2) return last1;  

		ForwardIterator1 ret = last1;

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (*it1 == *it2) {   
				++it1; ++it2;
				if (it2 == last2) { ret = first1; break; }
				if (it1 == last1) return ret;
			}
			++first1;
		}
		return ret;
	}

	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
	{
		if (first2 == last2) return last1;

		ForwardIterator1 ret = last1;

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (pred(*it1, *it2)) {
				++it1; ++it2;
				if (it2 == last2) { ret = first1; break; }
				if (it1 == last1) return ret;
			}
			++first1;
		}
		return ret;
	}

	//find_first_of

	template <class ForwardIterator1, class ForwardIterator2 >
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		                           ForwardIterator2 first2, ForwardIterator2 last2) 
	{
		while (first1 != last1) {
			for (ForwardIterator2 it = first2; it != last2; ++it) {
				if (*it == *first1)          // or: if (pred(*it,*first)) for version (2)
					return first1;
			}
			++first1;
		}
		return last1;
	}

	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
			                           ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
	{
		while (first1 != last1) {
			for (ForwardIterator2 it = first2; it != last2; ++it) {
				if (pred(*it, first1))          // or: if (pred(*it,*first)) for version (2)
					return first1;
			}
			++first1; 
		}
		return last1;
	}

	//search & search_n

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
		                    ForwardIterator2 first2, ForwardIterator2 last2)
	{
		if (first2 == last2) return first1; 

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (*it1 == *it2) {    
				if (it2 == last2) return first1;
				if (it1 == last1) return last1;
				++it1; ++it2;
			}
			++first1;
		}
		return last1;
	}

	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
	{
		if (first2 == last2) return first1;

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;
			while (pred(*it1,*it2)) {
				if (it2 == last2) return first1;
				if (it1 == last1) return last1;
				++it1; ++it2;
			}
			++first1;
		}
		return last1;
	}


	//search_n

	template<class ForwardIterator, class Size, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
		Size count, const T& value)
	{
		ForwardIterator it, limit;
		Size i;

		limit = first; std::advance(limit, std::distance(first, last) - count);

		while (first != limit)
		{
			it = first; i = 0;
			while (*it == value)       // or: while (pred(*it,val)) for the pred version
			{
				++it; if (++i == count) return first;
			}
			++first;
		}
		return last;
	}

	template<class ForwardIterator, class Size, class T, class BinaryPredicate>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
		Size count, const T& value, BinaryPredicate pred)
	{
		ForwardIterator it, limit;
		Size i;

		limit = first; std::advance(limit, std::distance(first, last) - count);

		while (first != limit)
		{
			it = first; i = 0;
			while (pred(*it, value))       
			{
				++it; if (++i == count) return first;
			}
			++first;
		}
		return last;
	}

	//equal

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, 
		       InputIterator2 first2,  BinaryPredicate pred)
	{
		while (first1 != last1) {
			if (pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}












	













}