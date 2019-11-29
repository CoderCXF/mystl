#pragma once
#include <cstddef>

namespace mystl {

	//five iterator type

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//iterator class tempalte

	template <class Category, class T, class Distance = ptrdiff_t, 
		      class Pointer = T*, class Reference = T&>
		struct iterator {
		typedef Category                    iterator_category;
		typedef T                           value_type;
		typedef Distance                    difference_type;
		typedef Pointer                     pointer;
		typedef Reference                   reference;
	};

	//iterator_traits(tool)

	template <class T>
	struct iterator_traits {
		typedef typename T::iterator_category           iterator_category;
		typedef typename T::value_type                  value_type;
		typedef typename T::difference_type             difference_type;
		typedef typename T::pointer                     pointer;
		typedef typename T::reference                   reference;
	};

	//template partial specialization, deal with native pointers

	template <class T>
	struct iterator_traits<T *> {
		typedef T                                       value_type;
		typedef ptrdiff_t                               difference_type;
		typedef random_access_iterator_tag              iterator_category;
		typedef T*                                      pointer;
		typedef T&                                      refernece;
	};

	template <class T>
	struct iterator_traits<const T *> {
		typedef T                                      value_type;
		typedef ptrdiff_t                              difference_type;
		typedef random_access_iterator_tag             iterator_category;
		typedef const T*                               pointer;
		typedef const T&                               refernece;
	};

	//global function template:extraction of iterator_category

	template <class Iterator>
	typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator &) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//global function template:extraction of value_type

	template <class Iterator>
	typename iterator_traits<Iterator>::value_type *
	value_type(const Iterator &) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//global function template:extraction of differnece_type
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type *
	difference_type(const Iterator &) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//assist function of <iterator>
	//distance(): calculate the diatance of two iterator
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}

	template <class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
	_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		return last - first;
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return _distance(first, last, category());
	}

	//advance() : Forward or Backward of iterator
	template <class InputIterator, class Distance>
	void _advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--) ++i;
	}

	template <class BidirectionalIterator, class Distance>
	void _advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
		if (n >= 0) {
			while (n--) ++i;
		}
		else
			while (n++) --i;
	}

	template <class RandomAccessIterator, class Distance>
	void _advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
		i += n;
	}

	template <class Iterator, class Distance>
	void advance(Iterator& i, Distance n) {
		_advance(i, n, iterator_category(i));
	}

	//next() : forward of iterator
	template<class ForwardIterator>
	typename iterator_traits<ForwardIterator>::difference_type
	_next(ForwardIterator& i, forward_iterator_tag) {
		return i += 1;
		return i;
	}

	template <class ForwardIterator, class Distance>
	typename iterator_traits<ForwardIterator>::difference_type
	_next(ForwardIterator& i, Distance n, forward_iterator_tag) {
		_advance(i, n, iterator_category(i));
		return i;
	}

	template<class BidirectionalIterator>
	typename iterator_traits<BidirectionalIterator>::difference_type
	_next(BidirectionalIterator& i, bidirectional_iterator_tag) {
		i += 1;
		return i;
	}

	template <class BidirectionalIterator, class Distance>
	typename iterator_traits<BidirectionalIterator>::difference_type
	_next(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
		_advance(i, n, bidirectional_iterator_tag);
		return i;
	}

	template<class RandomAccessIteratr>
	typename iterator_traits<RandomAccessIteratr>::difference_type
	_next(RandomAccessIteratr& i, random_access_iterator_tag) {
		i += 1;
		return i;
	}

	template <class RandomAccessIteratr, class Distance>
	typename iterator_traits<RandomAccessIteratr>::difference_type
	_next(RandomAccessIteratr& i, Distance n, random_access_iterator_tag) {
		_advance(i, n, random_access_iterator_tag);
		return i;
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
	next(Iterator& i) {
		_next(i, iterator_category(i));
	}

	template <class Iterator, class Distance>
	typename iterator_traits<Iterator>::difference
	next(Iterator& i, Distance n) {
		_next(i, n, iterator_category(i));
	}

	//prev() not be realized
	
	/**************************************************************
	 *Realize Iterator Adapter :(adapter of noramal iterator)
	 *reverse iterator && inserter iterator && stream iterator && move iterator
	***************************************************************/
	template <class Iterator>
	class reverse_iterator {
	protected:
		Iterator current;

	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type        value_type;
		typedef typename iterator_traits<Iterator>::difference_type   difference_type;
		typedef typename iterator_traits<Iterator>::pointer           pointer;
		typedef typename iterator_traits<Iterator>::reference         reference;

		typedef Iterator iterator_type;              //represent the normal iterator
		typedef reverse_iterator<Iterator> self;     //represent the reverse iterator
	public:
		explicit reverse_iterator(iterator_type i) :current(i) {}
		reverse_iterator(const self& rhs) :current(rhs.current) {}

		iterator_type base() const { return current; }
		reference operator*() const { Iterator tmp = current; return *--tmp }  //*(current - 1 ).value == reverse_iterator.value
		pointer operator->() const{ return &(operator*()); }
		self operator++() { --current; return *this; }
		self operator++(int) { self tmp = *this; --current; return tmp; }
		self operator--() { ++current; return *this; }
		self operator--(int) { self tmp = *this; ++current; return tmp; }
		self operator+(difference_type n) { return self(current - n); }
		self operator-(difference_type n) { return self(current + n); }
		reference operator[](difference_type n) { return *(*this + n); }   //this is a pointer of reverse_iterator
	};

	//overload of operator-

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs,
		   	  const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	//overload of operator==

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs,
		            const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	//overload of operator<

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
		           const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() < lhs.base();
	}

	//overload of operator!=

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
		            const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}
	//overload of operator>

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
		           const reverse_iterator<Iterator>& rhs)
	{
		return rhs < lhs;
	}

	//overload of operator<=

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
		            const reverse_iterator<Iterator>& rhs)
	{
		return !(rhs < lhs);
	}

	//overload of operator>=

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
		            const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs < rhs);
	}



	

}