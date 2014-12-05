// Lagrange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

double Fx(double x)
{
	return 3 * x - cos(x) - 1;
}

double Gx(double x, int n, double * rPointsPtr, double * rFxPtr)
{
	double result = 0;
	//для суммы
	for (int i = 0; i < n; i++)
	{
		double iX = rPointsPtr[i];
		double iFx = rFxPtr[i];

		double jResult = 1;		
	    //для произведения 
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				double jX = rPointsPtr[j];
				jResult *= (x - jX) / (iX - jX);
			}
		}

		result += iFx * jResult;
	}

	return result;
}

void Cheb(double a, double b, int n, double * chPoints, double * chFx)
{
	const double PI = 3.141592653589793238463;

	for (int i = 0; i < n; i++)
	{
		double point = 0.5 * (cos((2.0 * i + 1.0) * PI / (2.0 * (n + 1.0)))* (b - a) + b + a);
		chPoints[i] = point;
		chFx[i] = Fx(point);
		cout << point << "; " << endl;
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = 10;
	double rPoints[n] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double rFx[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	double chPoints[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double chFx[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Cheb(1, 10, n, chPoints, chFx);

	// рассчитываем F(x1), F(x2) ... F(xn)
	for (int i = 0; i < n; i++)
	{
		double x = rPoints[i];
		rFx[i] = Fx(x);
	}

	while (true)
	{		
		cout << "x = ";

		double x;
		cin >> x;

		double gx = Gx(x, n, rPoints, rFx);
		double fx = Fx(x);

		double gxCh = Gx(x, n, chPoints, chFx);
				
		cout << "g(x) = " << gx << endl << "f(x) = " << fx << endl << "* g(x) = " << gxCh << endl << endl;
	}

	return 0;
}



