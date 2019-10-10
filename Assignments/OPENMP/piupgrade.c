#include<stdio.h>
#include<omp.h>

// This is for solving FALSE SHARING

static long num_steps = 1000000000; // total number of division
double step; // width of rectangle
#define PAD 8
#define NUM_THREADS 1 // no of threads you want
int main()
{
	int i ,team;
	double x,pi,sum_of_height[NUM_THREADS][PAD];
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS); // setting the number of threads
	double before = omp_get_wtime();
	#pragma omp parallel
	{
		int i,id,nthreads;
		double x;
		id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		if(id == 0)
			team = nthreads;
		for(i=id,sum_of_height[id][0]=0.0; i<num_steps; i=i+nthreads)
		{
			x=(i+0.5)*step;
			sum_of_height[id][0] += 4.0/(1.0+x*x);
		}
	}
	for(i=0,pi=0.0;i<team;i++)
	{
		pi += sum_of_height[i][0] * step;
	}

	double after = omp_get_wtime();

	printf("PI : %1f Time : %1f\n",pi,after - before);
}  
