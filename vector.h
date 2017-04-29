#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <cstdlib>
#include <utility>
#include <algorithm>

template < typename T >
class vector
{
public:
	typedef T * iterator;
	typedef T const * const_iterator;

	vector();
	vector(vector const & b);
	vector(vector && b);
	explicit vector(size_t n, T const & v = T());
	template < typename Iter, typename = typename std::iterator_traits<Iter>::iterator_category >
	vector(Iter first, Iter last);
	~vector();

	void swap(vector & b);
	vector & operator = (vector const & b);
	vector & operator = (vector && b);
	void assign(size_t n, T const & v = T());
	template < typename Iter, typename = typename std::iterator_traits<Iter>::iterator_category >
	void assign(Iter first, Iter last);

	T & operator [](size_t i);
	T const & operator [](size_t i) const;
	T & front();
	T const & front() const;
	T & back();
	T const & back() const;
	T * data();
	T const * data() const;

	bool empty() const;
	size_t size() const;
	void reserve(size_t n);
	size_t capacity() const;
	void shrink_to_fit();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	void clear();
	void push_back(T const & v);
	void push_back(T && v);
	void pop_back();
	iterator insert(iterator pos, T const & v);
	iterator insert(iterator pos, T && v);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	void resize(size_t n, T const & v = T());

private:
	T * _data;
	size_t _size, _capacity;

	void _setCapacity(size_t n);
	static size_t _nextCapacity(size_t n);
};

template < typename T >
bool operator == (vector<T> const & a, vector<T> const & b);
template < typename T >
bool operator != (vector<T> const & a, vector<T> const & b);
template < typename T >
bool operator < (vector<T> const & a, vector<T> const & b);
template < typename T >
bool operator > (vector<T> const & a, vector<T> const & b);
template < typename T >
bool operator <= (vector<T> const & a, vector<T> const & b);
template < typename T >
bool operator >= (vector<T> const & a, vector<T> const & b);


template < typename T >
vector<T>::vector() :
	_data(nullptr), _size(0), _capacity(0)
{}

template < typename T >
vector<T>::vector(vector const & b) :
	vector(b.begin(), b.end())
{
}

template < typename T >
vector<T>::vector(vector && b) :
	_data(b._data), _size(b._size), _capacity(b._capacity)
{
	b._data = nullptr;
	b._size = b._capacity = 0;
}

template < typename T >
vector<T>::vector(size_t n, T const & v) :
	vector()
{
	reserve(n);
	for (size_t i = 0; i < _size; ++i)
		push_back(v);
}

template < typename T >
template < typename Iter, typename >
vector<T>::vector(Iter first, Iter last) :
	vector()
{
	for (Iter it = first; it != last; ++it)
		push_back(*it);
}

template < typename T >
vector<T>::~vector()
{
	for (size_t i = 0; i < _size; ++i)
		_data[i].~T();
	delete [] (char*)_data;
}

template < typename T >
void vector<T>::swap(vector & b)
{
	std::swap(_data, b._data);
	std::swap(_size, b._size);
	std::swap(_capacity, b._capacity);
}

template < typename T >
vector<T> & vector<T>::operator = (vector const & b)
{
	vector copy = b;
	swap(copy);
	return *this;
}

template < typename T >
vector<T> & vector<T>::operator = (vector && b)
{
	swap(b);
	return *this;
}

template < typename T >
void vector<T>::assign(size_t n, T const & v)
{
	*this = vector(n, v);
}

template < typename T >
template < typename Iter, typename >
void vector<T>::assign(Iter first, Iter last)
{
	*this = vector(first, last);
}

template < typename T >
T & vector<T>::operator [](size_t i)
{
	return _data[i];
}

template < typename T >
T const & vector<T>::operator [](size_t i) const
{
	return _data[i];
}

template < typename T >
T & vector<T>::front()
{
	return *_data;
}

template < typename T >
T const & vector<T>::front() const
{
	return *_data;
}

template < typename T >
T & vector<T>::back()
{
	return _data[_size - 1];
}

template < typename T >
T const & vector<T>::back() const
{
	return _data[_size - 1];
}

template < typename T >
T * vector<T>::data()
{
	return _data;
}

template < typename T >
T const * vector<T>::data() const
{
	return _data;
}

template < typename T >
bool vector<T>::empty() const
{
	return !_size;
}

template < typename T >
size_t vector<T>::size() const
{
	return _size;
}

template < typename T >
void vector<T>::reserve(size_t n)
{
	if (_capacity < n)
		_setCapacity(n);
}

template < typename T >
size_t vector<T>::capacity() const
{
	return _capacity;
}

template < typename T >
void vector<T>::shrink_to_fit()
{
	_setCapacity(_size);
}


template < typename T >
typename vector<T>::iterator vector<T>::begin()
{
	return iterator(_data);
}

template < typename T >
typename vector<T>::const_iterator vector<T>::begin() const
{
	return const_iterator(_data);
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cbegin() const
{
	return const_iterator(_data);
}

template < typename T >
typename vector<T>::iterator vector<T>::end()
{
	return iterator(_data + _size);
}

template < typename T >
typename vector<T>::const_iterator vector<T>::end() const
{
	return const_iterator(_data + _size);
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cend() const
{
	return const_iterator(_data + _size);
}

template < typename T >
void vector<T>::clear()
{
	erase(begin(), end());
}

template < typename T >
void vector<T>::push_back(T const & v)
{
	if (_size == _capacity)
	{
		T v1 = v;
		_setCapacity(_capacity == 0 ? 1 : (_capacity * 3 + 1) / 2);
		new (_data + _size++) T(std::move(v1));
	} else
		new (_data + _size++) T(v);
}

template < typename T >
void vector<T>::push_back(T && v)
{
	if (_size == _capacity)
	{
		T v1 = std::move(v);
		_setCapacity(_capacity == 0 ? 1 : (_capacity * 3 + 1) / 2);
		new (_data + _size++) T(std::move(v1));
	} else
		new (_data + _size++) T(v);
}

template < typename T >
void vector<T>::pop_back()
{
	_data[--_size].~T();
}

template < typename T >
typename vector<T>::iterator vector<T>::insert(iterator it, T const & v)
{
	size_t i = it - begin();
	push_back(v);
	for (size_t j = _size - 1; j != i; --j)
		std::swap(_data[j], _data[j - 1]);
	return begin() + i;
}

template < typename T >
typename vector<T>::iterator vector<T>::insert(iterator it, T && v)
{
	size_t i = it - begin();
	push_back(v);
	for (size_t j = _size - 1; j != i; --j)
		std::swap(_data[j], _data[j - 1]);
	return begin() + i;
}

template < typename T >
typename vector<T>::iterator vector<T>::erase(iterator pos)
{
	for (iterator it = pos + 1; it != end(); ++it)
		std::swap(*(it - 1), *it);
	pop_back();
	return pos;
}

template < typename T >
typename vector<T>::iterator vector<T>::erase(iterator first, iterator last)
{
	iterator res = first;
	while (last != end())
	{
		std::swap(*first, *last);
		++first;
		++last;
	}
	size_t newSize = first - _data;
	while (_size != newSize)
		pop_back();
	return res;
}

template < typename T >
void vector<T>::resize(size_t n, T const & v)
{
	if (n <= _size)
	{
		for (size_t i = n; i < _size; ++i)
			_data[i].~T();
		_size = n;
	} else {
		size_t newCapacity = _capacity == 0 ? 1 : _capacity;
		while (newCapacity < n)
			newCapacity = _nextCapacity(newCapacity);
		_setCapacity(newCapacity);
		for (size_t i = _size; i < n; ++i)
			new (_data + i) T(v);
		_size = n;
	}
}

template < typename T >
void vector<T>::_setCapacity(size_t n)
{
	n = std::max(n, _size);
	if (n == _capacity)
		return;
	T * newData = (T*)new char[n * sizeof(T)];
	for (size_t i = 0; i < _size; ++i)
	{
		try
		{
			new (newData + i) T(std::move(_data[i]));
		} catch (...)
		{
			for (size_t j = 0; j < i; ++j)
				newData[j].~T();
			delete [] (char*)newData;
			throw;
		}
	}
	for (size_t i = 0; i < _size; ++i)
		_data[i].~T();
	delete [] (char*)_data;
	_data = newData;
	_capacity = n;
}

template < typename T >
size_t vector<T>::_nextCapacity(size_t n)
{
	return n == 0 ? 4 : n * 3 / 2;
}

template < typename T >
bool operator == (vector<T> const & a, vector<T> const & b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

template < typename T >
bool operator != (vector<T> const & a, vector<T> const & b)
{
	return !(a == b);
}

template < typename T >
bool operator < (vector<T> const & a, vector<T> const & b)
{
	size_t s = std::min(a.size(), b.size());
	for (size_t i = 0; i < s; ++i)
		if (a[i] != b[i])
			return a[i] < b[i];
	return a.size() < b.size();
}

template < typename T >
bool operator > (vector<T> const & a, vector<T> const & b)
{
	return b < a;
}

template < typename T >
bool operator <= (vector<T> const & a, vector<T> const & b)
{
	return !(b < a);
}

template < typename T >
bool operator >= (vector<T> const & a, vector<T> const & b)
{
	return !(a < b);
}

namespace std
{
	template < typename T >
	void swap(vector < T > & a, vector < T > & b)
	{
		a.swap(b);
	}
}

#endif // __MYVECTOR_H__
