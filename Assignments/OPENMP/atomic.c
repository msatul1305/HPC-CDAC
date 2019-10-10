#include<stdio.h>
#include<omp.h>

static long num_steps = 1000000000;
double step;
#define NUM_THREADS 4
void main()
{
	double pi = 0.0;
	int team;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	double before = omp_get_wtime();
	#pragma omp parallel
	{
		int i, id, nthreads;
		double x, sum;
		id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		if (id == 0)
			team = nthreads;
		for (i = id, sum = 0.0 ; i<num_steps; i = i + team)
		{
			x = (i + 0.5) * step;	
			sum += 4.0/(1.0 + x*x);
		}
		sum = sum * step;
		#pragma omp atomic
			pi += sum;
	}
	double after = omp_get_wtime();
	printf("PI : %lf , Time : %f \n", pi, after - before);
}
