#include "vector.h"
#include <iostream>

template class vector<int>;

template < class T >
std::ostream & operator << (std::ostream & out, vector < T > const & x)
{
	out << '[';
	for (size_t i = 0; i < x.size(); ++i)
	{
		out << x[i];
		if (i + 1 != x.size())
			out << ',';
	}
	return out << ']';
}

template < class T >
std::ostream & operator << (std::ostream & out, vector < vector < T > > const & x)
{
	out << "[\n";
	for (size_t i = 0; i < x.size(); ++i)
	{
		out << "  " << x[i];
		if (i + 1 != x.size())
			out << ',';
		out << '\n';
	}
	return out << ']';
}

vector < vector < int > > c;

int main()
{
	vector < int > a;
	a.push_back(2);
	a.push_back(24);
	a.push_back(22);
	a.push_back(123);
	a.push_back(-1);
	c.push_back(a);
	a.push_back(-1);
	c.push_back(a);
	a.push_back(-1);
	a.push_back(123);
	c.push_back(a);
	std::cerr << a << "\n";
	auto b = a;
	a.pop_back();
	c.push_back(a);
	std::cerr << a << "\n";
	a.clear();
	c.push_back(a);
	std::cerr << a << "\n";
	std::cerr << b << "\n";
	std::cerr << vector<int>(b.begin() + 2, b.begin() + 5) << "\n\n";
	c.push_back(b);

	std::cerr << b << "\n";
	b.erase(b.begin() + 3);
	c.push_back(b);
	std::cerr << b << "\n";
	std::sort(b.begin(), b.end());
	c.push_back(b);

	std::cerr << c << "\n";
	std::sort(c.begin(), c.end());
	std::cerr << c << "\n";
	c.erase(c.begin() + 1);
	std::cerr << c << "\n";

	auto c1 = c;
	c1.pop_back();
	std::cerr << c1 << "\n";

	return 0;
}
