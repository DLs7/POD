#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "quicksort.h"

#define INPUT "arq0.txt"
#define SIZE 31

void systemCall(){
    printf("Pressione qualquer tecla para continuar...");
    getchar();
    system("clear");
}

void randomFile(char * fileName, int size, int offset) {
    FILE * file = fopen(fileName, "w");

    for (int i = 0; i < size + offset; i++){
        if(i < size){
            int num = rand() % 100;
            fprintf(file, "%d ", num);
            printf("%d ", num);
        } else {
            fprintf(file, "%d ", INT_MIN);
            printf("%d ", INT_MIN);
        }
    }
    fclose(file);

    printf("\n\n");
    systemCall();
}

int firstSizeFibonacci(int size) {
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

int secondSizeFibonacci(int size) {
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
    return second - first;
}

int nthFibonacci(int size) {
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
    return c;
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

int polyphaseMerge(int exec, int lastSize, int lastLastSize, int offset) {
    int blockSize = fibonacci(exec);

    if(SIZE + offset >= blockSize){
        printf("Blocksize: %d\nLast blocksize: %d\nLast last blocksize: %d\n", blockSize, lastSize, lastLastSize);

        int * buffer = (int*)malloc(sizeof(int) * blockSize);

        //arq 0
        if(exec % 3 == 0){
            FILE * file0 = fopen("arq0.txt", "w");
            FILE * file1 = fopen("arq1.txt", "r");
            FILE * file2 = fopen("arq2.txt", "r");

            while(!feof(file2)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file1, "%d", &buffer[i]);
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file2, "%d", &buffer[lastSize + i]);
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

            printf("\n\nRemovendo %d numeros\n\n", (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize));
            for (int i = 0; i < (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize); i++){
                removeFirstElement("arq1.txt");
                removeFirstElement("arq2.txt");
            }

            fclose(file0);
            fclose(file1);
            fclose(file2);

            systemCall();

        //arq 2
        } else if (exec % 3 == 1) {
            FILE * file0 = fopen("arq0.txt", "r");
            FILE * file1 = fopen("arq1.txt", "r");
            FILE * file2 = fopen("arq2.txt", "w");

            while(!feof(file1)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file0, "%d", &buffer[i]);
                    //removeFirstElement("arq0.txt");
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file1, "%d", &buffer[lastSize + i]);
                    //removeFirstElement("arq1.txt");
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

            printf("\n\nRemovendo %d numeros\n\n", (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize));
            for (int i = 0; i < (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize); i++){
                removeFirstElement("arq0.txt");
                removeFirstElement("arq1.txt");
            }

            fclose(file0);
            fclose(file1);
            fclose(file2);

            systemCall();
        
        //arq 1
        } else if (exec % 3 == 2) {
            FILE * file0 = fopen("arq0.txt", "r");
            FILE * file1 = fopen("arq1.txt", "w");
            FILE * file2 = fopen("arq2.txt", "r");

            while(!feof(file0)){
                for(int i = 0; i < lastSize; i++){
                    fscanf(file2, "%d", &buffer[i]);
                    //removeFirstElement("arq2.txt");
                }
                for(int i = 0; i < lastLastSize; i++){
                    fscanf(file0, "%d", &buffer[lastSize + i]);
                    //removeFirstElement("arq0.txt");
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

            printf("\n\nRemovendo %d numeros\n\n", (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize));
            for (int i = 0; i < (fibonacci(nthFibonacci(SIZE + offset) - exec) * lastSize); i++){
                removeFirstElement("arq2.txt");
                removeFirstElement("arq0.txt");
            }


            fclose(file0);
            fclose(file1);
            fclose(file2);

            systemCall();

        }
        free(buffer);
        return polyphaseMerge(exec + 1, blockSize, lastSize, offset);
    }
    return exec - 1;
}

void printFile(char * fileName) {
    FILE *file = fopen(fileName, "r");
    int n;
    printf("%s - ", fileName);
    while (fscanf(file, "%d", &n) == 1) 
        printf("%d ", n);
    
    printf("\n");
}

void startPolyphase(char * fileName, int * separation, int offset) {
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

    printFile("arq1.txt");
    printFile("arq2.txt");

    printf("\n");
    systemCall();

    int exec = polyphaseMerge(3, 1, 1, offset);

    printf("Final execution: %d\n\n", exec);

    if(exec % 3 == 0){
        for(int i = 0; i < offset; i++){
            removeFirstElement("arq0.txt");
        }
        printf("RESULTADO FINAL:\n");
        printFile("arq0.txt");

    } else if(exec % 3 == 1){
        for(int i = 0; i < offset; i++){
            removeFirstElement("arq2.txt");
        }
        printf("RESULTADO FINAL:\n");
        printFile("arq2.txt");

    } else if(exec % 3 == 2){
        for(int i = 0; i < offset; i++){
            removeFirstElement("arq1.txt");
        }
        printf("RESULTADO FINAL:\n");
        printFile("arq1.txt");
    }
    printf("\n");

    systemCall();
}

int main() {
    srand(time(NULL));
    system("clear");

    int * separation = (int*)malloc(sizeof(int) * 2);
    for(int i = 0; i < 2; i++){
        if(i == 0)
            separation[i] = firstSizeFibonacci(SIZE);
        else
            separation[i] = SIZE - separation[i - 1];
    }

    int offset = secondSizeFibonacci(SIZE) - separation[1];
    
    randomFile(INPUT, SIZE, offset);
    startPolyphase(INPUT, separation, offset);

    free(separation);
}