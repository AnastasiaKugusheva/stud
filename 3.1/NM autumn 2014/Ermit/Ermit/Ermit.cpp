// Ermit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

double Fx(double x)
{
	return 3 * x - cos(x) - 1;
}

double dFx(double x)
{
	return 3 + sin(x);
}

double Lx(double x, int n, double * rPointsPtr, double * rFxPtr)
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

double dLx(double x)
{
	return -4.9 * x + 11.31;
}

double Px(double x, int n, double * rPointsPtr)
{
	double result = 1;

	for (int i = 0; i < n; i++)	
		result *= x - rPointsPtr[i];
	
	return result;
}

double dPx(double x, int n, double * rPointsPtr)
{	
	return 3 * x * x - 12 * x + 11;
}

double H2x(double x, int n, double * rPointsPtr, double * rFxPtr)
{
	return (dFx(x) - dLx(x)) / dPx(x, n, rPointsPtr);	 
}

double H5x(double x, int n, double * rPointsPtr, double * rFxPtr)
{
	return Lx(x, n, rPointsPtr, rFxPtr) + H2x(x, n, rPointsPtr, rFxPtr) * Px(x, n, rPointsPtr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = 3;
	double rPoints[n] = { 1, 10, 20 };
	double rFx[n] = { 0, 0, 0 };

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

		double gx = H5x(x, n, rPoints, rFx);
		double fx = Fx(x);

		cout << "g(x) = " << gx << endl << "f(x) = " << fx << endl << endl;
	}

	return 0;
}