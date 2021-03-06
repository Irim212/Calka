 // Calka.cpp : Defines the entry point for the console application.
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
	double step = 1.0/ 1000000.0;
	int k, i;
/*
#pragma omp parallel for schedule(static) private(k) firstprivate(integral) shared(step)
	for (k = 1; k <= 100; k++)
	{

#pragma omp parallel for schedule(static) private (i) shared(k, step) reduction(+:integral)
		for (i = 1; i <= 1000000; i++)
		{
			integral += (cos(sqrt(k)*(i*step))) / (1.0 + sqrt(k));
		}

		integral *= step;
		printf("Całka dla k: %i = %f \n", k, integral);
	}*/

	
#pragma omp parallel for private (k, i, integral) shared(step)
	for (int k = 1; k <= 100; k++)
	{
		integral = 0;

		for (int i = 1; i <= 1000000; i++)
		{
			integral += (cos(sqrt(k)*(i*step))) / (1.0 + sqrt(k));
		}

		integral *= step;
		printf("Całka dla k: %i = %f \n", k, integral);
	}

	_getch();
	return 0;
}
