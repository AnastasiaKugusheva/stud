// MPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

float CalculateD(float derivative[4], float X[3])
{
	return derivative[0] * X[0] + derivative[1] * X[1] + derivative[2] * X[2] + derivative[3];
}

int _tmain(int argc, _TCHAR* argv[])
{
	float expression[10] = {
		//x^2 y^2 z^2  xy xz yz  x   y  z 
		2.0, 3.8, 4.8, 1, 1, -1, 1, -2, 3, 8
	};
	float eps = 0.01;

	float derivativeX1[4];
	derivativeX1[0] = expression[0] * 2; //X
	derivativeX1[1] = expression[3]; //Y
	derivativeX1[2] = expression[4]; //Z
	derivativeX1[3] = expression[6]; //0

	float derivativeX2[4];
	derivativeX2[0] = expression[3]; //X
	derivativeX2[1] = expression[1] * 2; //Y
	derivativeX2[2] = expression[5]; //Z
	derivativeX2[3] = expression[7]; //0

	float derivativeX3[4];
	derivativeX3[0] = expression[4]; //X
	derivativeX3[1] = expression[5]; //Y
	derivativeX3[2] = expression[2] * 2; //Z
	derivativeX3[3] = expression[8]; //0

	float X0[3] = {
		1, 1, 1
	};

	float X[3];
	float p = 1;

	int counter = 0;

	while (p > eps)
	{
		counter++;

		X[0] = (-1 * derivativeX1[1] * X0[1] - derivativeX1[2] * X0[2] - derivativeX1[3]) / derivativeX1[0];
		X[1] = (-1 * derivativeX2[0] * X[0] - derivativeX2[2] * X0[2] - derivativeX2[3]) / derivativeX2[1];
		X[2] = (-1 * derivativeX3[0] * X[0] - derivativeX3[1] * X[1] - derivativeX3[3]) / derivativeX3[2];

		//check stop
		float P[3];
		P[0] = X[0] - X0[0];
		P[1] = X[1] - X0[1];
		P[2] = X[2] - X0[2];

		//norma
		p = sqrt(P[0] * P[0] + P[1] * P[1] + P[2] * P[2]);

		cout << "Continue " << p << endl;

		X0[0] = X[0];
		X0[1] = X[1];
		X0[2] = X[2];
	}

	cout << "Succes!" << endl;
	cout << "Count: " << counter << endl;

	cout << "X" << ": " << X[0] << endl;
	cout << "Y" << ": " << X[1] << endl;
	cout << "Z" << ": " << X[2] << endl;

	system("pause");
	return 0;
}
