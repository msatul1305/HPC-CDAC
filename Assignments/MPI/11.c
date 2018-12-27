#include<stdio.h>
#include<mpi.h>
#define n 100
int main(){
char name[n];
sprintf(name,"Atul Kumar Agrawal");
MPI_Init();
MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	if(comm_sz%2==0)
	{
	printf("%s",name);
	}
	else
	{
	printf("error!");
	}
MPI_Finalize();
return 0;
}
