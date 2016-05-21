#include<stdio.h>
#include<mpi.h>


int hashData(int );

int main(int argc, char * argv[]){
int my_rank;
int comm_sz;
int source;
int localResponse=0;
int totalResponse=0;
int dicLenght;
//diccionario a considerar
int diccionario[50]={3,5,9,14,25,33,41,45,57,67,68,69,71,73,74,75,77,84,86,89,93,94,99,103,107,113,114,117,123,129,130,133,137,139,143,146, 151,157,165,171};


int iter;
int dicLength;
int dicChunkInit,dicChunkEnd;

dicLength=sizeof(diccionario);
// recuperamos los parametros 
// target: objetivo a buscar
// nProcc: numero de procesos en paralelo
//nProcc=atoi(argv[2]);
int target=atoi(argv[1]);

MPI_Init(NULL,NULL);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

if (my_rank!=0){

}

if (my_rank!=0){
	dicChunkInit=(my_rank-1)*(dicLength)/comm_sz;
	dicChunkEnd=(my_rank)*(dicLength)/comm_sz;	
	localResponse=0;
	for (iter=dicChunkInit;iter<dicChunkEnd;iter++){
		if (hashData(diccionario[iter])==hashData(target)){
			localResponse=1;
		}
	}
	MPI_Send(&localResponse, 1, MPI_INT,0,0,MPI_COMM_WORLD);
} else {
	totalResponse=localResponse;
	for(source=1; source < comm_sz; source++){
		MPI_Recv(&localResponse,1,MPI_INT,source,0,MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		totalResponse+=localResponse;
	}
}
if(my_rank==0){
	printf("Encontrado %d\n",totalResponse);
	
}
MPI_Finalize();
return 0;



}

int hashData(int num){
	return num;
}
