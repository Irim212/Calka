// CalkaPodwojna.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <omp.h>
#include <chrono>
#include <conio.h>


int main()
{
	omp_set_nested(1);

	double integral = 0.0;
	double integralOut = 0.0;
	double step = 1.0 / 10000.0;

	double powX, powY;
	
	int i, j;
	for (int z = 0; z < 50; z++)
	{

/*
#pragma omp parallel for schedule(static) private (i, integral, powX) shared(step) reduction(+:integralOut)
		for (i = 1; i <= 10000; i++)
		{
			integral = 0.0;
			powX = (i*step)*(i*step);

#pragma omp parallel for schedule(static) private (j, powY) shared(i, powX, step) reduction (+:integral)
			for (j = 1; j <= 10000; j++)
			{
				powY = (j*step)*(j*step);
				integral += exp(-(powX + powY)) / (1 + powX + powY);
			}
			integralOut += integral;
		}
		*/
		
	#pragma omp parallel for schedule(static) private (i, j, powX, powY) shared (step) reduction(+:integral)
		for (int i = 1; i <= 10000; i++)
		{
			powX = (i*step)*(i*step);

			for (int j = 1; j <= 10000; j++)
			{
				powY = (j*step)*(j*step);
				integral += exp(-(powX + powY)) / (1 + powX + powY);
			}
		}

		integral *= step * step;

		printf("Całka : = %f \n", integral);
	}
	

	_getch();
	return 0;
}

