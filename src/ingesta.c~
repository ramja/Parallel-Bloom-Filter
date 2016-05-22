#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "dict_spanish.txt"
typedef struct dicto{
    char **values;
    int length;
} dicto;

dicto buildDicto(){
	
	dicto d;
        FILE * infile;
        char line[121];
        char ** info = NULL;
        int llen;
        int counter = 0;

        int backdown;

        infile = fopen(FILE_NAME,"r");

        while (fgets(line,120,infile)) {

        // Allocate memory for pointer to line just added
                d.values = realloc(d.values,(counter+1) * sizeof(char *));
        // And allocate memory for that line itself!
                llen = strlen(line);
                d.values[counter] = calloc(sizeof(char),llen+1);
        // Copy the line just read into that memory
                strcpy(d.values[counter],line);

                //printf("%d characters in line %d \n",llen,counter);
                counter++;
        }

        //for (backdown = counter-1; backdown >= 0; backdown--) {
        //        printf("%d: %s",backdown,info[backdown]);
        //        }
	
	d.length = counter;
	printf("%d\n",d.length);
	return d;
}
//#include "Functions.h"
/*
int main(){
	dicto d;
	printf("Aqui");
	d = buildDicto();
	
	int i;
	for (i = 0; i < d.length; i++) {
                printf("%d: %s",i,d.values[i]);
                }
}*/
