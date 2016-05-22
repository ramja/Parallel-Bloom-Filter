#include<stdio.h>
#include<string.h>
#include<mpi.h>//incluye funciones macros y types

const int MAX_STRING=100;

int main(void){

	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;
	int q;
	MPI_Init(NULL, NULL);//realiza el setup - alojar espacio para mensajes - decidr rangos
//normalmente MPI_Init(&argc, &argv);
//MPI_COMM_WORLD es un comunicator que consiste de todos los procesos iniciados
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);//devuelve el numero total de procesos como int
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);//devuelve el rango de cada proceso como int

	if(my_rank != 0){//todos los que no son el Master
	//sprintf mete a mensaje la cadena que le sigue
		sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
//MPI_Send --> mensaje - apuntador, largo del mensaje en int aqui +1 para el caracter \0, tipo de mensaje - MPI_CHAR o MPI_INT o MPI_FLOAT o MPI_DOUBLE, a que proceso int, un tag un entero no negativo para saber que mensaje es, un communicator  
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR,0,0,MPI_COMM_WORLD);
	}else{
		printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
		for (q=1; q < comm_sz; q++){
//MPI_Recv --> mensaje apuntador out variable, int buf size pueden ser almacenados, MPI_Datatype buf_type, int source rank, int source tag, MPI_Comm comunicator, MPI_Status
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//Truco - se puede usar MPI_ANY_SOURCE en source de receive para no tener que esperar a que lleguen todos 
//Igualmente com MPI_ANY_TAG para los tags
//MPI_Status status;
//En MPI_Recv(...,&status)
//stauts.MPI_SOURCE
//status MPI_TAG
//MPI_Get_Count(&status,recv_type,&count) permite obtener el tamaño del mensaje

			printf("%s\n",greeting);

		}

	}

	MPI_Finalize();
	return 0;




}
