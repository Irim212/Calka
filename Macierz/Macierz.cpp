// Macierz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <omp.h>

const int size = 1000;

int matrix1[size][size];
int matrix2[size][size];
int vector[size];
int matrixMatrix[size][size];
int matrixVector[size];

int main()
{
	srand(time(NULL));
	omp_set_nested(1);

	int i, j, k;
	int sumMatrix, sumVector;

	for (i = 0; i < size; i++)
	{
		vector[i] = ((double)rand() / RAND_MAX);

		for (j = 0; j < size; j++)
		{
			matrix1[i][j] = ((double)rand()/RAND_MAX);
			matrix2[i][j] = ((double)rand()/RAND_MAX);
		}
	}

#pragma omp parallel for schedule(static) private (i, sumMatrix, sumVector) shared (size, j, k, sumVector, matrix1, matrix2, vector)
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			sumMatrix = 0;
			sumVector += matrix1[i][j] * vector[j];

			for (k = 0; k < size; k++)
			{
				sumMatrix += matrix1[i][k] * matrix2[k][j];
			}
			matrixMatrix[i][j] = sumMatrix;
		}
		matrixVector[i] += sumVector;
	}

	/*
	for (i = 0; i < size; i++)
	{
		sumVector = 0;

#pragma omp parallel for schedule(static) private (j, sumMatrix) shared (vector, k, matrix1, matrix2, size) reduction(+:sumVector)
		for (j = 0; j < size; j++)
		{
			sumMatrix = 0;
			sumVector += matrix1[i][j] * vector[j];

#pragma omp parallel for schedule(static) private (k) shared (matrix1, matrix2, size) reduction (+:sumMatrix)
			for (k = 0; k < size; k++)
			{
				sumMatrix += matrix1[i][k] * matrix2[k][j];
			}
			matrixMatrix[i][j] = sumMatrix;
		}
		matrixVector[i] += sumVector;
	}*/

    return 0;
}

