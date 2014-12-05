// Newton1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h> 
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// f(x)= 3x-cosx-1
	// f'(x)= 3+sinx
	// f''(x) = cosx 
	// [-0.2;0]
	
	float eps = 0.0001;	
	float x0 = 0; 

	float k;
	int i = 0;
	do
	{
		float fx = 3 * x0 - cos(x0) - 1;
		float dfx = 3 + sin(x0);
		float x = x0 - fx / dfx;
		k = abs(x - x0);
		x0 = x;
		i++;
		cout << "x = " << x << endl;
	} while (k > eps);

	
	cout << "count = " << i;


	char c;
	cin >> c;
	

	return 0;
}

