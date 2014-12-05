// NewtSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GaussMethod.h"
#include <math.h> 
#include <iostream>


using namespace std;

float f1(float x, float y)
{
	return cos(x) + y - 1.5;
}

float f2(float x, float y)
{
	return 2 * x - sin(y - 0.5) - 1;
}


float df1x(float x, float y)
{
	return -1 * sin(x);
}

float df1y(float x, float y)
{
	return 1;
}

float df2x(float x, float y)
{
	return 2;
}

float df2y(float x, float y)
{
	return -1 * cos(0.5 - y);
}

int _tmain(int argc, _TCHAR* argv[])
{

	float eps = 0.0001;

	float x0 = 0.6;
	float y0 = 0.7;

	//gn = ?
	//hn = ?

	// df1x * gn + df1y * hn = -1 * f1
	// df2x * gn + df2y * hn = -1 * f2
	
	bool k;
	int i = 0;
	do
	{
		i++;
		float Matrix[2][3] = {
			{ df1x(x0, y0), df1y(x0, y0), -1 * f1(x0, y0) },
			{ df2x(x0, y0), df2y(x0, y0), -1 * f2(x0, y0) }
		};

		float result[2];
		Gauss(Matrix, result);

		float gn = result[0];
		float hn = result[1];

		float xn = x0 + gn;
		float yn = y0 + hn;

		k = abs(xn - x0) > eps || abs(yn - y0) > eps;

		x0 = xn;
		y0 = yn;

		cout << "x" << i << " = " << x0 << ";\t y" << i << " = " << y0 << endl;

	} while (k);

	cout << endl << "x= " << x0 << ";\t y= " << y0 << endl;

	system("pause");

	return 0;
}

