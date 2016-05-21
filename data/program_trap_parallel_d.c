#include <stdio.h>
#include <mpi.h>
#include"trapecio.c"

int main(int argc, char **argv){
	int my_rank;
	int comm_sz;
	
	double  parametros[3]; //Parametros:
	
	int local_n;
	double a, b, h; //change this values in other implementation
	double local_a;
	double local_b;
	double local_int; //estimate of trapezoid in cpu my _rank
	double total_int;
	int source;
	int dest;
	int rc;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	if(my_rank == 0){
		scanf("n=%d",  &parametros[0]);	
   		scanf("a=%lf", &parametros[1]);
		scanf("b=%lf", &parametros[2]);
		if(n%comm_sz != 0) {
			printf("El numero de trapecios debe ser múltiplo del número de procesos\n");
			MPI_Abort(MPI_COMM_WORLD, rc);
			exit(1);
		}
		MPI_Bcast(&parametros,3,MPI_DOUBLE,0,MPI_COMM_WORLD);
    }
	


	h=(b-a)/n; /*h is the same for all processes*/
	local_n= n/comm_sz; /* number of trapezoids, same for all processes*/
	
	
	local_a = a+my_rank*local_n*h;
	local_b = local_a+local_n*h;
	local_int=Trap(local_a, local_b, local_n, h);


	MPI_Reduce(&local_int,&total_int,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	

	if(my_rank==0){
		printf("Integral from %f to %f = %.15e\n", a, b, total_int);
	}


	MPI_Finalize();
	return 0;
} /*main*/
