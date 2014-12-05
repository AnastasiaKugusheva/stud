// Spline.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

double Hx(int x, double* points)
{
	x++;
	return points[x] - points[x - 1];
}

double Fxk(int k, double* points, double* fx)
{
	k++;
	return (fx[k] - fx[k - 1]) / Hx(k - 1, points);
}

double* A(int n, double* fx)
{
	double* a = new double[n];
	for (int i = 0; i < n; i++)
		a[i] = fx[i];
	return a;
}

double* B(double* c, double* d, int n, double* points, double* fx)
{
	double* b = new double[n];
	b[0] = Fxk(0, points, fx) + 2.0 / 3.0 * c[0] * Hx(0, points);
	for (int k = 1; k < n; k++)
	{
		double hk = Hx(k, points);
		b[k] = Fxk(k, points, fx) + 2.0 / 3.0 * c[k] * hk + 1.0 / 3.0 * hk * c[k - 1];
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
			lambda[i] = (3.0 * Fxk(k, points, fx) - 3.0 * Fxk(k - 1, points, fx) - hi * lambda[k - 2])
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

const int N = 50;
const double START_X = 0.1;
const double STEP_X = 0.1;

void Sx(double* points, double* fx)
{
	int n = N - 1;
	double* a = A(n, fx);
	double* c = C(n, points, fx);
	double* d = D(c, n, points);
	double* b = B(c, d, n, points, fx);

	double p = START_X;
	for (int i = 0; i < n; i++)
	{
		double xi = points[i];
		double ai = a[i];
		double bi = b[i];
		double ci = c[i];
		double di = d[i];

		double next = p + STEP_X;

		cout << "[" << p << ";"<< next << "]: " << ai << "+(" << bi << ")(x-" << xi << ")+("<< ci << ")(x-"<< xi << ")^2+(" << di << ")(x-" << xi << ")^3" << endl;

		p = next;
	}
	
	delete[] a;
	delete[] b;
	delete[] c;
	delete[] d;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	double points[N];
	double p = START_X;
	for (int i = 0; i < N; i++)
	{
		points[i] = p;
		p += STEP_X;
	}

	double fx[N] = { 28.55, 29.40, 31.00, 31.60, 33.00, 34.15, 35.50, 36.90, 38.15, 39.70, 41.10, 42.45, 44.00, 46.00, 47.70, 49.50, 51.70, 53.40, 55.00, 57.30, 59.20, 60.75, 63.00, 64.90, 66.40, 68.30, 69.80, 71.60, 73.20, 74.65, 76.30, 77.20, 78.60, 79.30, 80.50, 81.35, 82.20, 83.00, 83.90, 84.40, 84.90, 85.10, 85.40, 85.45, 85.50, 85.50, 85.80, 85.90, 84.90, 84.20 };
	
	Sx(points, fx);

	char c;
	cin >> c;

	return 0;
}

