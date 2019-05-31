#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quicksort.h"

#define INPUT "arq0.txt"
#define SIZE 21

void randomFile(char * fileName, int size) {
    FILE * file = fopen(fileName, "w");

    for (int i = 0; i < size; i++){
        int num = rand() % 100;
        fprintf(file, "%d ", num);
        printf("%d ", num);
    }

    fclose(file);
}

int sizeFibonacci(int size) {
    int c = 0, next = 0, first = 0, second = 1;
    
    while(next < size) {
        if(c <= 1)
            next = c;
        else{
            next = first + second;
            first = second;
            second = next;
        }
        c++;
    }

    return first;
}

int fibonacci(int n) { 
    if (n <= 1) 
        return n; 
    return fibonacci(n-1) + fibonacci(n-2); 
} 

void copyFile(char* file1Name, char* file2Name)
{
    FILE *file1 = fopen(file1Name, "w");
    FILE *file2 = fopen(file2Name, "r");

    int n;
    while (fscanf(file2, "%d", &n) == 1) 
        fprintf(file1, "%d ", n);

    fclose(file1);
    fclose(file2);
}

void removeFirstElement(char *fileName)
{
    FILE *file = fopen (fileName, "r");
    FILE *fileAux = fopen ("temp.txt", "w");

    int n;
    fscanf(file, "%d", &n);
    while (fscanf(file, "%d", &n) == 1) fprintf(fileAux, "%d ", n);

    fclose(file);
    fclose(fileAux);

    copyFile(fileName, "temp.txt");
    remove("temp.txt");
}

void polyphaseMerge(int exec, int lastSize, int lastLastSize) {
    int blockSize = lastSize + lastLastSize;
    
    if(SIZE >= blockSize){

        printf("\n\n\nBlocksize: %d\nLast blocksize: %d\nLast last blocksize: %d\n", blockSize, lastSize, lastLastSize);

        int * buffer = (int*)malloc(sizeof(int) * blockSize);

        //arq 0
        if(exec % 3 == 0){
            FILE * file0 = fopen("arq0.txt", "w");
            FILE * file1 = fopen("arq1.txt", "r");
            FILE * file2 = fopen("arq2.txt", "r");

            while(!feof(file2)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file1, "%d", &buffer[i]);
                    removeFirstElement("arq1.txt");
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file2, "%d", &buffer[lastSize + i]);
                    removeFirstElement("arq2.txt");
                }
                
                if(!feof(file2)){
                    quick_sort(buffer, blockSize);
                    printf("\n");
                    for(int i = 0; i < blockSize; i++){
                        printf("%d ", buffer[i]);
                        fprintf(file0, "%d ", buffer[i]);
                    }
                }
            }

            fclose(file0);
            fclose(file1);
            fclose(file2);

        //arq 2
        } else if (exec % 3 == 1) {
            FILE * file0 = fopen("arq0.txt", "r");
            FILE * file1 = fopen("arq1.txt", "r");
            FILE * file2 = fopen("arq2.txt", "w");

            while(!feof(file1)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file0, "%d", &buffer[i]);
                    removeFirstElement("arq0.txt");
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file1, "%d", &buffer[lastSize + i]);
                    removeFirstElement("arq1.txt");
                }
                if(!feof(file1)){
                    quick_sort(buffer, blockSize);
                    printf("\n");
                    for(int i = 0; i < blockSize; i++){
                        printf("%d ", buffer[i]);
                        fprintf(file2, "%d ", buffer[i]);
                    }
                }
            }

            fclose(file0);
            fclose(file1);
            fclose(file2);
        
        //arq 1
        } else if (exec % 3 == 2) {
            FILE * file0 = fopen("arq0.txt", "r");
            FILE * file1 = fopen("arq1.txt", "w");
            FILE * file2 = fopen("arq2.txt", "r");

            while(!feof(file0)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file2, "%d", &buffer[i]);
                    removeFirstElement("arq2.txt");
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file0, "%d", &buffer[lastSize + i]);
                    removeFirstElement("arq0.txt");
                }
                if(!feof(file0)){
                    quick_sort(buffer, blockSize);
                    printf("\n");
                    for(int i = 0; i < blockSize; i++){
                        printf("%d ", buffer[i]);
                        fprintf(file1, "%d ", buffer[i]);
                    }
                }
            }

            fclose(file0);
            fclose(file1);
            fclose(file2);

        }

        polyphaseMerge(exec + 1, blockSize, lastSize);
    }
}

void startPolyphase(char * fileName, int * separation) {
    FILE * file0 = fopen("arq0.txt", "r");
    FILE * file1 = fopen("arq1.txt", "w");
    FILE * file2 = fopen("arq2.txt", "w");
    int num, i = 0;

    while((fscanf(file0 ,"%d", &num)) != EOF){
        if(i < separation[0]){
            fprintf(file1, "%d ", num);
        } else {
            fprintf(file2, "%d ", num);
        }
        i++;
    }

    fclose(file0);
    fclose(file1);
    fclose(file2);

    polyphaseMerge(3, 1, 1);
}

int main() {
    srand(time(NULL));
    randomFile(INPUT, SIZE);

    int * separation = (int*)malloc(sizeof(int) * 2);
    
    for(int i = 0; i < 2; i++){
        if(i == 0)
            separation[i] = sizeFibonacci(SIZE);
        else
            separation[i] = SIZE - separation[i - 1];
    }

    printf("\n\nSeparation: %d %d\n\n", separation[0], separation[1]);

    startPolyphase(INPUT, separation);
}