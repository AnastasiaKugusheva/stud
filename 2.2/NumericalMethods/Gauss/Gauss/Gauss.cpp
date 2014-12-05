// Gauss.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	float Matrix[4][5] = {
		{ 4.4, -2.5, 19.2, -10.8, 4.3 },
		{ 5.5, -9.3, -14.2, 13.2, 6.8 },
		{ 7.1, -11.5, 5.3, -6.7, -1.8 },
		{ 14.2, 23.4, -8.8, 5.3, 7.2 } };

	float sourceMatrix[4][5];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << Matrix[i][j] << "\t";

			sourceMatrix[i][j] = Matrix[i][j];
		}
		cout << endl;
	}
	//-------------

	int column = 0;

	for (int line = 0; line < 4; line++)
	{
		float k = Matrix[line][column];
		for (int i = column; i < 5; i++)
		{
			Matrix[line][i] = Matrix[line][i] / k;
		}

		for (int i = line + 1; i < 4; i++)
		{
			float multiplex = Matrix[i][column];
			for (int j = column; j < 5; j++)
			{
				Matrix[i][j] = Matrix[i][j] - Matrix[line][j] * multiplex;
			}
		}
		column++;
	}

	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}

	//------------


	int column1 = 3;

	for (int line1 = 3; line1 >= 0; line1--)
	{

		for (int i = line1 - 1; i >= 0; i--)
		{
			float x4 = Matrix[i][column1];
			for (int j = 4; j >= 0; j--)
			{
				Matrix[i][j] = Matrix[i][j] - Matrix[line1][j] * x4;
			}
		}
		column1--;
	}




	//---------------
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}

	float result[4];

	for (int i = 0; i < 4; i++)
	{
		cout << "x" << i << " = " << Matrix[i][4] << endl;
		result[i] = Matrix[i][4];
	}

	//---------prove solution 

	for (int i = 0; i < 4; i++)
	{


		float summator = 0;
		for (int j = 0; j < 4; j++)
		{
			summator += sourceMatrix[i][j] * result[j];
		}

		if (summator - sourceMatrix[i][4] < 0.001)
		{
			cout << "success" << "\t" << "equation" << i + 1 << endl;
		}
	}

	system("pause");
	return 0;
}

