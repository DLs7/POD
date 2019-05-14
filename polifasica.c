#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void randomFile (char *fileName, int size);

void randomFile (char *fileName, int size) 
{
    FILE *file = fopen (fileName, "w");

    for (int i = 0; i<size; i++) {
        int n = rand()%100;
        fprintf(file, "%d ", n);
    }

    fprintf(file, "%d", -1);

    fclose(file);

    return;
}

int main() {
    randomFile("randomNumbers.txt", 16);
}