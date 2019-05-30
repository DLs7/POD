#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kway.h"

#define RAM 3

// File manipulation functions
void concatFiles(char* file1Name, char* file2Name) 
{
    FILE *file1 = fopen(file1Name, "r+");
    FILE *file2 = fopen(file2Name, "r");

    // Go to the end of file1.
    fseek(file1, 0, SEEK_END);

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

void printFile(char* fileName)
{
    FILE *file = fopen(fileName, "r");
    int n;
    printf("%s - ", fileName);
    while (fscanf(file, "%d", &n) == 1) 
        printf("%d ", n);
    
    printf("\n");
}

void createSortedFile(int numberWays, char* fileName)
{
    initializeTempWays(numberWays);
    getNFirsts(numberWays);

    int buffer[RAM];
    clearBuffer(buffer);
    initializeBuffer(buffer);
    
    FILE *sortedFile = fopen(fileName, "w");
    fclose(sortedFile);

    int h =0;

    while (1) {
        if (buffer[0] == -1 && buffer[1] == -1 && buffer[2] == -1) {
            break;
        }
        
        printBuffer(buffer);

        int lesserIndex = getLesserValue(buffer);
        FILE *aux = fopen(fileName, "r+");
        fseek(aux, 0, SEEK_END);
        fprintf(aux, "%d ", buffer[lesserIndex]);
        fclose(aux);

        buffer[lesserIndex] = -1;

        char tempWayName[15] = {'t', 'e', 'm', 'p', 'W', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getTempWayName(lesserIndex, tempWayName);
        FILE *tempWay = fopen(tempWayName, "r");
        int n;
        if (fscanf(tempWay, "%d", &n) == 1) {
            buffer[lesserIndex] = n;
            removeFirstElement(tempWayName);
        }

        fclose(tempWay);
    }
 
    printBuffer(buffer);
}

// Buffer manipulation functions
void initializeBuffer(int *buffer)
{
    for (int i = 0; i<RAM; i++) {
        char tempWayName[15] = {'t', 'e', 'm', 'p', 'W', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getTempWayName(i, tempWayName);
        FILE *tempWay = fopen(tempWayName, "r");
        int n;
        if (fscanf(tempWay, "%d", &n) == 1) {
            buffer[i] = n;
        }

        removeFirstElement(tempWayName);

        fclose(tempWay);
    }
}

void clearBuffer(int* buffer) 
{
    for (int i = 0; i<RAM; i++) 
        buffer[i] = -1;
}

void sortBuffer (int *buffer)
{
    for (int i = 1; i < RAM; i++) {
        int key = buffer[i];
        int j = i-1;
        while ( (j >= 0) && (key < buffer[j]) && key > 0) {
            buffer[j+1] = buffer[j];
            j--;
        }
        buffer[j+1] = key;  
    }
}

void printBuffer(int *buffer)
{
    for (int i = 0; i<RAM; i++) {
        printf("%d ", buffer[i]);
    }

    printf("\n");
}

void concatBufferFile(int *buffer, char* fileName) 
{
    FILE *file = fopen(fileName, "r+");
    // Go to the end of file.
    fseek(file, 0, SEEK_END);
    for (int i = 0; i<RAM; i++) {
        // Only values different than -1 are allowed.
        if (buffer[i] != -1)
            fprintf(file, "%d ", buffer[i]);
    }

    fclose(file);
}

int getLesserValue (int *buffer)
{
    int lesser = 0;

    for (int i = 0; i<RAM; i++) {
        
        if (buffer[i] != -1) {
            if (buffer[i] < buffer[lesser])
        	    lesser = i;
        } 
    }

    return lesser;
}

// Way manipulation functions
void initializeWays(int numberWays)
{
    for (int i = 0; i<numberWays; i++) {
        char wayName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getWayName(i, wayName);
        FILE *way = fopen(wayName, "w");
        fclose(way);
    }
}

void initializeTempWays(int numberWays)
{
    for (int i = 0; i<numberWays; i++) {
        char tempWayName[15] = {'t', 'e', 'm', 'p', 'W', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getTempWayName(i, tempWayName);
        FILE *tempWay = fopen(tempWayName, "w");
        fclose(tempWay);
    }
}

void removeTempWays(int numberWays)
{
    for (int i = 0; i<numberWays; i++) {
        char tempWayName[15] = {'t', 'e', 'm', 'p', 'W', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getTempWayName(i, tempWayName);
        remove(tempWayName);
    }
}

static void printWays(int numberWays) 
{
    char wayName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
    for (int i = 0; i<numberWays; i++) {
        getWayName(i, wayName);
        printFile(wayName);
    }
}

void createFirstWays(int numberWays, char* fileName)
{
    if (numberWays < 1) {
        printf("Invalid number of ways in fuction createFirstWays. Number of ways must be a positive and bigger than 0 value.\n");
        return;
    } 

    FILE *dataFile = fopen(fileName, "r");
    
    int buffer[RAM];
    char wayName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
    
    int n;
    int i = 0;
    int aWay = 0;
    while (fscanf(dataFile, "%d", &n) == 1) {
        if (i == RAM) {
            i = 0;

            getWayName(aWay, wayName);
            sortBuffer(buffer);
            concatBufferFile(buffer, wayName);
            clearBuffer(buffer);

            if (aWay == numberWays-1) 
                aWay = 0;
            else
                aWay++;

        }
        
        buffer[i] = n;
    
        i++;
    }
    getWayName(aWay, wayName);
    sortBuffer(buffer);
    concatBufferFile(buffer, wayName);
    clearBuffer(buffer);


    fclose(dataFile);

    printf("createFirstWays:\n");
    printWays(numberWays);
}

void createWays(int numberWays, char* fileName)
{
}

void kWays(int numberWays, char* fileName)
{
    initializeWays(numberWays);
    createFirstWays(numberWays, fileName);
    createSortedFile(numberWays, "sortedFile.txt");
}

void getWayName(int index, char* wayName)
{
    char aux[4] = {'0', '0', '0', '\0'};

    if (index > 999 || index < 0) {
        printf("Index out of scope of function getWayName.\n");
        return;
    }

    if (index < 9) {
        aux[2] = index + 48;
        
    } else if (index < 99) {
        aux[1] = ( index / 10 ) + 48;
        aux[2] = ( index % 10 ) + 48;
        
    } else if (index < 999) {
        aux[0] = ( index / 100 ) + 48;
        aux[1] = ( ( index / 10 ) % 10 ) + 48;
        aux[2] = ( index % 10 ) + 48;
    }

    for (int i = 0; i<3; i++) {
        wayName[3+i] = aux[i];
    }
}

void getTempWayName(int index, char* tempWayName)
{
    char aux[4] = {'0', '0', '0', '\0'};

    if (index > 999 || index < 0) {
        printf("Index out of scope of function getWayName.\n");
        return;
    }

    if (index < 9) {
        aux[2] = index + 48;
        
    } else if (index < 99) {
        aux[1] = ( index / 10 ) + 48;
        aux[2] = ( index % 10 ) + 48;
        
    } else if (index < 999) {
        aux[0] = ( index / 100 ) + 48;
        aux[1] = ( ( index / 10 ) % 10 ) + 48;
        aux[2] = ( index % 10 ) + 48;
    }

    for (int i = 0; i<3; i++) {
        tempWayName[7+i] = aux[i];
    }
}

void getNFirsts(int numberWays)
{
    for (int i = 0; i<numberWays; i++) {
        char tempWayName[15] = {'t', 'e', 'm', 'p', 'W', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        char wayName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        getWayName(i, wayName);
        getTempWayName(i, tempWayName);

        FILE *way = fopen(wayName, "r");
        FILE *tempWay = fopen(tempWayName, "w");

        int n;
        int j = 0;
        while (fscanf(way, "%d", &n) == 1 && j < RAM) {
            fprintf(tempWay, "%d ", n);
            j++;
        }

        for (int j = 0; j<RAM; j++) {
            removeFirstElement(wayName);
        }

        fclose(way);
        fclose(tempWay);
    }
}

void main ()
{
    kWays(3, "testFile.txt");

}