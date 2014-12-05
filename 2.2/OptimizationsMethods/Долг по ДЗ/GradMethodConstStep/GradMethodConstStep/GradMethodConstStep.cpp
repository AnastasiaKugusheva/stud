// GradMethodConstStep.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

float CalculateD(float derivative[4], float X[3])
{
	return
		(derivative[0] * X[0] + derivative[1] * X[1] + derivative[2] * X[2] + derivative[3]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	float expression[10] = {
		//x1^2 x2^2 x3^2 x1x2 x1x3 x2x3 x1 x2 x3 
		3.0,      5.0,    4.0,    2.0, - 1.0, - 1.0,   7.0,  0.0, 1.0
	};

	float eps = 0.01;

	float derivativeX1[4];
	derivativeX1[0] = expression[0] * 2; //x
	derivativeX1[1] = expression[3]; //y
	derivativeX1[2] = expression[4]; //z
	derivativeX1[3] = expression[6]; //0

	float derivativeX2[4];
	derivativeX2[0] = expression[3]; //x
	derivativeX2[1] = expression[1] * 2; //y
	derivativeX2[2] = expression[5]; //z
	derivativeX2[3] = expression[7]; //0

	float derivativeX3[4];
	derivativeX3[0] = expression[4]; //x
	derivativeX3[1] = expression[5]; //y
	derivativeX3[2] = expression[2] * 2; //z
	derivativeX3[3] = expression[8]; //0

	float X0[3] = {
		1, 1, 1
	};

	float D0[3];
	D0[0] = CalculateD(derivativeX1, X0);
	D0[1] = CalculateD(derivativeX2, X0);
	D0[2] = CalculateD(derivativeX3, X0);

	int counter = 0;

	float L = 0.01;
	while (true) {

		counter++;

		float X[3];
		X[0] = X0[0] - L*D0[0];
		X[1] = X0[1] - L*D0[1];
		X[2] = X0[2] - L*D0[2];

		//check stop
		float P[3];
		P[0] = CalculateD(derivativeX1, X);
		P[1] = CalculateD(derivativeX2, X);
		P[2] = CalculateD(derivativeX3, X);
		float p = sqrt(P[0] * P[0] + P[1] * P[1] + P[2] * P[2]);

		if (p <= eps)
		{
			cout << "Success!" << endl;
			cout << "Count: " << counter << endl;
			for (int i = 0; i < 3; i++)
				cout << "X" << i << ":" << X[i] << endl;
			break;
		}
		else
			cout << "Continue" << p << endl;

		float D01[3];
		D01[0] = CalculateD(derivativeX1, X0);
		D01[1] = CalculateD(derivativeX2, X0);
		D01[2] = CalculateD(derivativeX3, X0);
		

		D0[0] = D01[0];
		D0[1] = D01[1];
		D0[2] = D01[2];


		X0[0] = X[0];
		X0[1] = X[1];
		X0[2] = X[2];

	}

	char c;
	cin >> c;
	return 0;
}

