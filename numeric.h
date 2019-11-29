#pragma once
/*********************************
 *The header contains Numeric Algorithm
 *accumlate();innner_product();partial_sum();adjacent_difference()
 *********************************/
#include "iterator.h"
namespace mystl {

	//accumlate

	template <class InputIterator, class T>
	T accumlate(InputIterator beg, InputIterator end, T init) {
		for (; beg != end; ++beg) {
			init += *beg;
		}
		return init;
	}

	template <class InputIterator, class T, class BinaryOperator>
	T accumlate(InputIterator beg, InputIterator end, T init, BinaryOperator binary_op) {
		init = binary_op(init, *beg);
		return init;
	}

	//inner_product

	template <class InputIterator, class T>
	T inner_product(InputIterator beg1, InputIterator end, InputIterator beg2, T init) {
		for (; beg1 != end; ++beg1, ++beg2) {
			init += ((*beg1) * (*beg2));
		}
		return init;
	}

	template <class InputIterator, class T, class BinaryOperator>
	T inner_product(InputIterator beg1, InputIterator end, InputIterator beg2, T init,
		            BinaryOperator op1, BinaryOperator op2) {
		for (; beg1 != end; ++beg1, ++beg2) {
			init = op1(init, op2(*beg1, *beg2));
		}
	}

	//partial_sum

	template <class InputIterator, class OutputIterator>
	OutputIterator partial_sum(InputIterator sourceBeg, InputIterator sourceEnd, OutputIterator destBeg) {
		if (sourceBeg == sourceEnd)
			*destBeg = *sourceBeg;
		auto value = *sourceBeg;
		while (++sourceBeg != sourceEnd) {
			value += *sourceBeg;
			*++destBeg = value;
		}
		return ++destBeg;
	}

	template <class InputIterator, class OutputIterator, class BinaryFun>
	OutputIterator partial_sum(InputIterator sourceBeg, InputIterator sourceEnd, OutputIterator destBeg,BinaryFun op) {
		if (sourceBeg == sourceEnd)
			*destBeg = *sourceBeg;
		auto value = *sourceBeg;
		while (++sourceBeg != sourceEnd) {
			value = op(value,*sourceBeg);
			*++destBeg = value;
		}
		return ++destBeg;
	}

	//adjacent_difference

	template <class InputIterator, class OutputIterator>
	OutputIterator adjacent_difference(InputIterator sourceBeg, InputIterator sourceEnd, OutputIterator destBeg) {
		if (sourceBeg == sourceEnd)
			*destBeg = *sourceBeg;
		auto value = *sourceBeg;
		while (++sourceBeg != sourceEnd) {
			value = value - *sourceBeg;
			*++destBeg = value;
		}
		return ++destBeg;
	}

	template <class InputIterator, class OutputIterator, class BinaryFun>
	OutputIterator adjacent_difference(InputIterator sourceBeg, InputIterator sourceEnd, OutputIterator destBeg, BinaryFun op) {
		if (sourceBeg == sourceEnd)
			*destBeg = *sourceBeg;
		auto value = *sourceBeg;
		while (++sourceBeg != sourceEnd) {
			value = op(value, *sourceBeg);
			*++destBeg = value;
		}
		return ++destBeg;
	}




}
