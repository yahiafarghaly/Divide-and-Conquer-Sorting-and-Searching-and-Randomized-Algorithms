#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string karatsuba_multi(string num1,string num2);
bool is_power_of_2 (int n)
{
	if(n == 0) return false;
	return ( (n & (~n + 1)) == n ); // n & 2's complement of n == n
}


int main(int argc, char** argv)
{
	string result = "";

	result = karatsuba_multi("12345","56789");


	std::cout << "The result = \n" << result << std::endl;
	return 0;
}

/*!
 *  Input: two n-digit positive integers x and y.
 *	Output: the product x · y.
 *  Assumption: n is a power of 2.
 *
 **/
string karatsuba_multi(string x,string y)
{

	if (x.size() == 1 && y.size() == 1)
		return to_string(stoll(x) * stoll(y));

	// Make sure they have the same size despite that
	// they may be both power of 2 of not
	if (x.size() != y.size())
	{
		if (x.size() > y.size())
			y.insert(0,x.size() - y.size(),'0');
		else
			x.insert(0,y.size() - x.size(),'0');
	}

	// check if n is not a power of 2, then adding extra trailing zeros
	while (!is_power_of_2(x.size()))
		x.insert(0,1,'0');

	while (!is_power_of_2(y.size()))
		y.insert(0,1,'0');

	int n = x.size();
	string a,b,c,d,p,q;
	string ac,bd,adbc,pq;

	a = x.substr(0,n/2);
	b = x.substr(n/2); // to the end of the string.

	c = y.substr(0,n/2);
	d = y.substr(n/2); // to the end of the string.

	/* Fail for large numbers such as 27182818284590452353602874713526 + 62497757247093699959574966967627
	   due to the lack of converting it to a valid integer data type that can contain a number beyond 64 bits

	Hint: you may write a recursive algorithm to add up the very very large numbers on my poor 64 bits machine !*/
	p = to_string( stoll(a) + stoll(b) );
	q = to_string( stoll(c) + stoll(d) );

	ac = karatsuba_multi(a,c);
	bd = karatsuba_multi(b,d);
	pq = karatsuba_multi(p,q);

	adbc = to_string ( stoll(pq) - stoll(ac) - stoll(bd) );

	return to_string( pow(10,n)*stoll(ac) + pow(10,n/2)*stoll(adbc) + stoll(bd) );
}
