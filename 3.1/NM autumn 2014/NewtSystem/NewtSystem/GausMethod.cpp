
#include "stdafx.h"
#include <iostream>

using namespace std;

void Gauss(float Matrix[][3], float * result)
{
	int column = 0;
	
	for (int line = 0; line < 2; line++)
	{
		float k = Matrix[line][column];
		for (int i = column; i < 3; i++)
		{
			Matrix[line][i] = Matrix[line][i] / k;
		}

		for (int i = line + 1; i < 2; i++)
		{
			float multiplex = Matrix[i][column];
			for (int j = column; j < 3; j++)
			{
				Matrix[i][j] = Matrix[i][j] - Matrix[line][j] * multiplex;
			}
		}
		column++;
	}

	/*cout << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}*/

	//------------


	int column1 = 1;

	for (int line1 = 1; line1 >= 0; line1--)
	{

		for (int i = line1 - 1; i >= 0; i--)
		{
			float x4 = Matrix[i][column1];
			for (int j = 1; j >= 0; j--)
			{
				Matrix[i][j] = Matrix[i][j] - Matrix[line1][j] * x4;
			}
		}
		column1--;
	}


	for (int i = 0; i < 2; i++)
	{
		/*cout << "x" << i << " = " << Matrix[i][2] << endl;*/
		result[i] = Matrix[i][2];
	}


	//---------------вывод гаусса
	/*cout << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}*/

	//---------prove solution 

	/*for (int i = 0; i < 4; i++)
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
	}	*/
	/*
	res[0] = result[0];
	res[1] = result[1];
	res[2] = result[2];
	res[3] = result[3];*/
}
