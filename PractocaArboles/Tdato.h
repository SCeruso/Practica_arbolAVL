#pragma once
#include <math.h>
#include <iostream>

using namespace std;

class tester
{
private:
	double n_;
	static double p_;
	static int cont_;
public:
	tester(double = 0.0);
	~tester();

	double& valor();
	static double& presicion();
	static int& contador();
	bool operator >(tester&);
	bool operator == (tester&);
	bool operator != (tester&);
	bool operator < (tester&);
	friend ostream& operator << (ostream&, tester);
};

