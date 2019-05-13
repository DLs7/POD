#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void errorMessage (int errorCode);
int createFile (char *fileName);
int createFiles (int numberFiles);
void intToChar (int number, char *fileName);
void randomFile (char *fileName, int size);
int createWays (int range, int numberWays, char *randomNumbersFileName);
int createWay (int *iteration, int index, int range, int numberWays, char *randomNumbersFileName);

// Error handling messages
void errorMessage (int errorCode)
{
    char* errorMessage;

    switch (errorCode) {
        case 1:
            errorMessage = "Unable to create file.\n";
            break;

        case 2:
            errorMessage = "Too much ways, the maximum is 999 ways.\n";
    }

    printf(errorMessage);
} 

// File creation
int createFile (char *fileName) 
{
    FILE *file;
    if ( ( file = fopen (fileName, "w") ) == NULL ) {
        errorMessage(1);
        fclose(file);
        return -1;
    
    } else {
        return 1;
    }
}

// Create X files
int createFiles (int numberFiles) 
{
    char fileIndex[2];
    char fileName[11] = {'w', 'a', 'y', 'i', 'i', 'i', '.', 't', 'x', 't', '\0'};
    for (int i = 0; i < numberFiles; i++) {
        
        intToChar (i, fileName);
        createFile(fileName);
    }

    return 1;
}

// Transform an int (0-999) to a char array.
void intToChar (int number, char *fileName)
{   
    char aux[4] = {'0', '0', '0', '\0'};

    if (number > 999) {
        //errorMessage(2);
        return;
    }

    if (number < 9) {
        aux[2] = number + 48;
        
    } else if (number < 99) {
        aux[1] = ( number / 10 ) + 48;
        aux[2] = ( number % 10 ) + 48;
        
    } else if (number < 999) {
        aux[0] = ( number / 100 ) + 48;
        aux[1] = ( ( number / 10 ) % 10 ) + 48;
        aux[2] = ( number % 10 ) + 48;
    }

    for (int i = 0; i<3; i++) {
        fileName[3+i] = aux[i];
    }
    
}

// Generate a file with random numbers.
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

int createWays (int range, int numberWays, char *randomNumbersFileName)
{
    createFiles(numberWays);
    int iteration = 0;

    int i = 0;
    int j = 0;
    int endOfFile;

    while (endOfFile != -1) {
        j = 0;
        
        if (i == numberWays) {
            i = 0;
        }
        
        while (endOfFile != -1 && j < numberWays) {
            endOfFile = createWay(&iteration, j, range, numberWays, randomNumbersFileName);
            j++;
        }

        i++;
    }
}

int createWay (int *iteration, int index, int range, int numberWays, char *randomNumbersFileName)
{
    char fileName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
    intToChar(index, fileName);

    printf("%s\n", fileName);

    FILE *auxWay = fopen ("auxWay.txt", "w");
    FILE *way = fopen (fileName, "r+");
    FILE *randomNumbers = fopen(randomNumbersFileName, "r");    

    int filePosition = *iteration;
    fseek (randomNumbers, filePosition, SEEK_SET);
    
    printf("Initial position = %d\n", filePosition);

    int number = *iteration;
    int rNumber;
    for (int i = 0; i<range; i++) {
        printf("Pos = %d ", number); 
        fscanf(randomNumbers, "%d", &rNumber);
        
        if (rNumber == -1) break;
        
        fprintf(auxWay, "%d ", rNumber);

        number+=2;
        if (rNumber > 9) number+=1;
        if (rNumber > 99) number+=1;

        printf("Number = %d\n", rNumber);
    }

    
    *iteration = number;

    if (rNumber == -1) return -1;
    fclose(way);
    fclose(randomNumbers);

    return 1;
}

int main ()
{
    srand(time(NULL));
    int range = 5;
    int numberWays = 3;
    randomFile("randomNumbers.txt", 16);
    createWays(range, numberWays, "randomNumbers.txt");

    return 1;
}