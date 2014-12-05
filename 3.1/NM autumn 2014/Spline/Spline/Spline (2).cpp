// Spline.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

double Fx(double x)
{
	return 3.0 * x - cos(x) - 1;
}

double Hx(int x, double* points)
{
	x++;
	return points[x] - points[x - 1];
}

double Fxk(int k, double* points, double* fx)
{
	k++;
	return (fx[k] - fx[k - 1]) / Hx(k, points);
}

double* A(int n, double* fx)
{
	double* a = new double[n];
	for (int i = 0; i < n + 1; i++)
		a[i] = fx[i];
	return a;
}

double* B(double* c, double* d, int n, double* points, double* fx)
{
	double* b = new double[n];
	for (int k = 0; k < n; k++)
	{
		double hk = Hx(k, points);
		b[k] = Fxk(k, points, fx) + c[k] * hk - d[k] * hk * hk;
	}
	return b;
}

double* C(int n, double* points, double* fx)
{
	// calculate delta and lambda
	double* delta = new double[n - 1];
	double* lambda = new double[n - 1];
	for (int i = 0; i < n - 1; i++)
	{
		int k = i + 1; // i = k-1
		if (i == 0)
		{
			double h1 = Hx(0, points);
			double h2 = Hx(1, points);
			delta[i] = -1.0 * h2 / (2.0 * h1 + 2.0 * h2);
			lambda[i] = (3.0 * Fxk(1, points, fx) - 3.0 * Fxk(0, points, fx))
				/ (2.0 * h1 + 2.0 * h2);
		}
		else
		{
			double hi = Hx(i, points);
			double hk = Hx(k, points);
			delta[i] = -1.0 * hk / (2.0 * hi + 2.0 * hk + hi * delta[k - 2]);
			lambda[i] = (3.0 * Fxk(k, points, fx) - 3.0 * Fxk(i, points, fx) - hi * lambda[k - 2])
				/ (2.0 * hi + 2.0 * hk + hi * delta[k - 2]);
		}
	}

	// calculate c
	double* c = new double[n];
	c[n - 1] = 0; // cn = 0
	for (int i = n - 1 - 1; i >= 0; i--)
	{
		int k = i + 1; // i = k-1
		c[i] = delta[i] * c[k] + lambda[i];
	}

	delete[] delta;
	delete[] lambda;

	return c;
}

double* D(double* c, int n, double* points)
{
	double* d = new double[n];
	d[0] = c[0] / (3.0 * Hx(0, points));
	for (int k = 1; k < n; k++)
		d[k] = (c[k] - c[k - 1]) / 3.0 * Hx(k, points);
	return d;
}

double Sx(double x, int N, double* points, double* fx)
{
	int n = N - 1;
	double* a = A(n, fx);
	double* c = C(n, points, fx);
	double* d = D(c, n, points);
	double* b = B(c, d, n, points, fx);

	int k = -1;
	for (int i = 0; i < N; i++)
	{
		if (points[i] > x)					
			break;
		else if (i == N -1)
		{
			k = N - 2;
			break;
		}

		k = i;
	}

	if (k != -1 && k < n)
	{
		double D = x - points[k];
		double ak = a[k];
		double bk = b[k];
		double ck = c[k];
		double dk = d[k];

		delete[] a;
		delete[] b;
		delete[] c;
		delete[] d;

		return ak + bk * D + ck * D * D + dk * D * D* D;
	}

	return NAN;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 10;
	double points[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	double fx[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < N; i++)
		fx[i] = Fx(points[i]);

	while (true)
	{
		cout << "x = ";

		double x;
		cin >> x;

		double sx = Sx(x, N, points, fx);
		double fx = Fx(x);

		cout << "S(x) = " << sx << endl << "f(x) = " << fx << endl << endl;
	}

	return 0;
}

