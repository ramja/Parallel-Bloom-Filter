#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "dict_spanish.txt"
#define MAX_DIC_LEN 100000
typedef struct dicto {
	char **values;
	int length;
} dicto;

int buildDicto(char ** d) {

	FILE * infile;
	char line[121];
	char ** info = NULL;
	int llen;
	int counter = 0;

	int backdown;

	infile = fopen(FILE_NAME, "r");

	while (fgets(line, 120, infile)) {

		// Allocate memory for pointer to line just added
		//  d= realloc(d,(counter+1) * sizeof(char *));
		// And allocate memory for that line itself!
		llen = strlen(line);
		d[counter] = calloc(sizeof(char), llen + 1);
		line[llen - 1] = '\0';
		// Copy the line just read into that memory
		strcpy(d[counter], line);

		//printf("%d characters in line %d \n",llen,counter);
		counter++;
	}

	//for (backdown = counter-1; backdown >= 0; backdown--) {
	//        printf("%d: %s",backdown,info[backdown]);
	//        }

	int length = counter;
//	printf("%d\n",length);
	return length;
}
//#include "Functions.h"
/*
 int main(){
 char * d[MAX_DIC_LEN ];
 int n = buildDicto(d);
 printf("%d\n",n);
 
 int i;
 for (i = 0; i < n; i++) {
 printf("%d: %s",i,d[i]);
 }
 }
 */
