// iNewton.cpp : Defines the entry point for the console application.
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
{	//массив b0..bn
	double * bPtr = new double[n];
	
	double result = 0;
	
	for (int i = 0; i < n; i++)
	{
		double iX = rPointsPtr[i];
		double iFx = rFxPtr[i];
		
		double resultSummand = 1;
		double bNumerator = iFx;
		double bDenominator = 1;
		for (int j = 0; j < i; j++)
		{
			resultSummand *= x - rPointsPtr[j];

			// calculate b
			double summand = bPtr[j];
			for (int k = 0; k < j; k++)
			{
				summand *= iX - rPointsPtr[k];
			}
			bNumerator -= summand;
			bDenominator *= iX - rPointsPtr[j];
		}
		double b = bNumerator / bDenominator;
		bPtr[i] = b;

		resultSummand *= b;
		
		result += resultSummand;
	}

	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int n = 10;
	double rPoints[n] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double rFx[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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

		cout << "g(x) = " << gx << endl << "f(x) = " << fx << endl << endl;
	}

	return 0;
}
