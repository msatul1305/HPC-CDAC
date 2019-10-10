#include<stdio.h>
#include<omp.h>

static long num_steps = 1000000000;
double step; 

#define NUM_THREADS 4

void main()
{
	double pi = 0.0;
	int team;
	step = 1.0/(double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double before = omp_get_wtime();
	#pragma omp parallel
	{
		int i, id, nthreads;
		double x, sum_up_height;
		id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		if(id == 0)
			team = nthreads;
		for ( i = id, sum_up_height = 0.0; i<num_steps; i = i + team)
		{
			x = (i + 0.5) * step;
			sum_up_height += 4.0/(1.0 + x*x);
		}
		#pragma omp critical
			pi += sum_up_height * step;
	}
	double after = omp_get_wtime();
	printf("PI: %lf, Time: %lf \n", pi, after - before);
}
