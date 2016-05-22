#include <stdio.h>
#include <mpi.h>
#include"trapecio_paralelo.c"

int main(int argc, char **argv){
	int my_rank;
	int comm_sz;
	int n; //number of trapezoids
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
                printf("por favor Introduzca el valor de a,b y n\n");
		scanf("%lf %lf %d", &a, &b, &n);
		
        }
	MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	

	if(n%comm_sz != 0 && my_rank == 0){
		printf("El numero de procesadores %d no es multiplo del numero de trapecios %d en efecto n mod comm_sz = %d\n",comm_sz,n,n%comm_sz);
  		MPI_Abort(MPI_COMM_WORLD, rc);
  		exit(1);
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
