#include<stdio.h>
#include<mpi.h>
#include <string.h>
#include "ingesta.c"

#define MAX_DIC_LEN 100000
#define TMANO_DIC 30
#define TMANO_LISTA 20
//int hashData(int );
int hashData(const char * stem, const char* stem2, int num);

int main(int argc, char * argv[]) {
	int my_rank;
	int comm_sz;
	int source;
	int localResponse = 0;
	int totalResponse = 0;
//diccionario a considerar
	char * diccionario[MAX_DIC_LEN];
	int dicLength = buildDicto(diccionario);
//	diccionario = dic.values;
//	dicLength = sizeof(diccionario);
//	char * diccionario[MAX_DIC_LEN] = { "azar", "atarugamiento", "atarugar",
////			"atasajada", "atasajado", "atasajar", "atascada", "atascadero",
////			"atascado", "atascamiento", "atascar", "atasco", "atasquería",
//			"ataúd", "ataudada", "ataudado", "ataujía", "ataujiada",
//			"ataujiado", "ataurique", "ataviar", "atávica", "atávico", "atavío",
//			"atavismo", "ataxia", "atáxica", "atáxico", "atea", "atear" };

	int iter;
	int dicChunkInit, dicChunkEnd;
	int listaPalabras[TMANO_LISTA] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int encontrado;
// recuperamos los parametros 
// target: objetivo a buscar
// nProcc: numero de procesos en paralelo
//nProcc=atoi(argv[2]);
	char * target = argv[1];
	int i;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	if (my_rank != 0) {

	}

	if (my_rank != 0) {
		dicChunkInit = (my_rank - 1);
		localResponse = -1;
		for (iter = dicChunkInit; iter < dicLength; iter = iter + comm_sz) {
			if (hashData(diccionario[iter], target, 3)
					&& hashFinalData(diccionario[iter], target, 3)) {
				localResponse = iter;
				MPI_Send(&localResponse, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
		MPI_Send(&localResponse, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	} else {
		i = 0;
		encontrado = 0;
		for (source = 1; source < comm_sz; source++) {
			MPI_Recv(&localResponse, 1, MPI_INT, source, 0, MPI_COMM_WORLD,
					MPI_STATUS_IGNORE);
			if (!(localResponse < 0) && i < TMANO_LISTA) {
				listaPalabras[i++] = localResponse;
				encontrado = 1;
			}
		}
	}
	if (my_rank == 0) {
		printf("Encontrado %d\n", encontrado);
		if (encontrado == 1) {
			i = 0;
			while (listaPalabras[i] >= 0) {
				printf("-%s\n", diccionario[listaPalabras[i++]]);
			}
		}

	}
	MPI_Finalize();
	return 0;

}

int hashData(const char * stem1, const char* stem2, int num) {
//	printf("hash:%s-%s\n",stem1,stem2);
	if (!memcmp(stem1, stem2, num)) {
		return 1;
	}

	return 0;
}
int hashFinalData(const char * stem1, const char* stem2, int num) {
	int len1 = strlen(stem1);
	int len2 = strlen(stem2);
	//printf("hash:%s-%s/n",stem1,stem2);
	if (len1 - num > 0 && len2 - num > 0) {

		if (!memcmp(stem1 + len1 - num, stem2 + len2 - num, num)) {
			return 1;
		}
	}

	return 0;
}
