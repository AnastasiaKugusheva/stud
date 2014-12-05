// PaireD0AD0D0itions1904.cpp : D0efines the entry point for the console application.
//

#include "stdafX.h"
#include <iostream>
#include <math.h>

using namespace std;

float CalculateD(float derivative[4], float X[3])
{
	return -1 *
		(derivative[0] * X[0] + derivative[1] * X[1] + derivative[2] * X[2] + derivative[3]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	float expression[10] = {
		//X1^2 X2^2 X3^2 X1X2  X1X3  X2X3  X1   X2   X3   0
		3.0, 5.0, 4.0, 2.0, -1.0, -1.0, 7.0, 0.0, 1.0, 0.0
	};
	float eps = 0.01;

	float derivativeX1[4];
	derivativeX1[0] = expression[0] * 2; //X1
	derivativeX1[1] = expression[3]; //X2
	derivativeX1[2] = expression[4]; //X3
	derivativeX1[3] = expression[6]; //0

	float derivativeX2[4];
	derivativeX2[0] = expression[3]; //X1
	derivativeX2[1] = expression[1] * 2; //X2
	derivativeX2[2] = expression[5]; //X3
	derivativeX2[3] = expression[7]; //0

	float derivativeX3[4];
	derivativeX3[0] = expression[4]; //X1
	derivativeX3[1] = expression[5]; //X2
	derivativeX3[2] = expression[2] * 2; //X3
	derivativeX3[3] = expression[8]; //0

	float X0[3] = {
		1, 1, 1
	};

	float D0[3];
	D0[0] = CalculateD(derivativeX1, X0);
	D0[1] = CalculateD(derivativeX2, X0);
	D0[2] = CalculateD(derivativeX3, X0);

	int counter = 0;
	while (true)
	{
		counter++;

		float L0 = (expression[0] * D0[0] * D0[0]
			+ expression[1] * D0[1] * D0[1]
			+ expression[2] * D0[2] * D0[2]
			+ expression[3] * D0[0] * D0[1]
			+ expression[4] * D0[0] * D0[2]
			+ expression[5] * D0[1] * D0[2]) * 2; // L
		float L1 = expression[0] * 2 * X0[0] * D0[0]
			+ expression[1] * 2 * X0[1] * D0[1]
			+ expression[2] * 2 * X0[2] * D0[2]
			+ expression[3] * X0[0] * D0[1]
			+ expression[3] * X0[1] * D0[0]
			+ expression[4] * X0[0] * D0[2]
			+ expression[4] * X0[2] * D0[0]
			+ expression[5] * X0[1] * D0[2]
			+ expression[5] * X0[2] * D0[1]
			+ expression[6] * D0[0]
			+ expression[7] * D0[1]
			+ expression[8] * D0[2]; // 0

		float L = -1 * L1 / L0; // alpha

		float X[3];
		X[0] = X0[0] + L*D0[0];
		X[1] = X0[1] + L*D0[1];
		X[2] = X0[2] + L*D0[2];

		//check stop
		float P[3];
		P[0] = -1 * CalculateD(derivativeX1, X);
		P[1] = -1 * CalculateD(derivativeX2, X);
		P[2] = -1 * CalculateD(derivativeX3, X);
		float p = sqrt(P[0] * P[0] + P[1] * P[1] + P[2] * P[2]);

		if (p <= eps)
		{
			cout << "Succes!" << endl;
			cout << "Count: " << counter << endl;
			for (int i = 0; i < 3; i++)
				cout << "X" << i << ": " << X[i] << endl;
			break;
		}
		else
			cout << "Continue " << p << endl;

		//norma X0
		float P0[3];
		P0[0] = -1 * CalculateD(derivativeX1, X0);
		P0[1] = -1 * CalculateD(derivativeX2, X0);
		P0[2] = -1 * CalculateD(derivativeX3, X0);

		float p0 = sqrt(P0[0] * P0[0] + P0[1] * P0[1] + P0[2] * P0[2]);

		//betta
		float b = p * p / (p0 * p0);

		//D01
		float D01[3];
		D01[0] = -1 * P[0] + b*D0[0];
		D01[1] = -1 * P[1] + b*D0[1];
		D01[2] = -1 * P[2] + b*D0[2];


		// repeat
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


//float X1[3][2];
//X1[0][0] = D0[0]; // L
//X1[0][1] = X0[0];// 0
//X1[1][0] = D0[1];
//X1[1][1] = X0[1];
//X1[2][0] = D0[2];
//X1[2][1] = X0[2];