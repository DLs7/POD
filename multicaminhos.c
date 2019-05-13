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
void sortFile (char *fileName);
int sizeFile (char *fileName);
int* createArrayFromFile (char *fileName, int size);
void sortArray (int *array, int size);
void concatFiles (char *fileName1, char *fileName2);
void kWays (int numberWays);
void createFileFromArray (char *fileName, int *array, int size);
void removeFirstElementFile (char *fileName);
int getLesserValue (int *array, int size);

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

    FILE *auxWay = fopen ("auxWay.txt", "w");
    FILE *way = fopen (fileName, "r+");
    FILE *randomNumbers = fopen(randomNumbersFileName, "r");    

    int filePosition = *iteration;
    fseek (randomNumbers, filePosition, SEEK_SET);

    int number = *iteration;
    int rNumber;
    for (int i = 0; i<range; i++) {
        fscanf(randomNumbers, "%d", &rNumber);
        
        if (rNumber == -1) break;
        
        fprintf(auxWay, "%d ", rNumber);

        number+=2;
        if (rNumber > 9) number+=1;
        if (rNumber > 99) number+=1;
    }

    *iteration = number;

    fclose(auxWay);
    
    sortFile("auxWay.txt");

    fclose(way);
    fclose(randomNumbers);

    concatFiles(fileName, "auxWay.txt");

    if (rNumber == -1) return -1;
    return 1;
}

void sortFile (char *fileName)
{
    int size = sizeFile(fileName);
    int *array = createArrayFromFile(fileName, size);
    sortArray(array, size);

    FILE *file = fopen (fileName, "w");
    for (int i = 0; i<size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);
}

int* createArrayFromFile (char *fileName, int size)
{
    FILE *file = fopen (fileName, "r");

    int *aux = malloc(size);

    for (int i = 0; i<size; i++) {
        fscanf(file, "%d", &aux[i]);
    }

    fclose(file);
    return aux;
}

void sortArray (int *array, int size)
{
    for (int i = 1; i < size; i++) {
        int chave = array[i];
        int j = i-1;
        while ( (j >= 0) && (chave < array[j]) ) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = chave;  
    }
}

int sizeFile (char *fileName) 
{
    FILE *file = fopen (fileName, "r");
    int n;
    int size = 0;

    while (fscanf(file, "%d", &n) == 1) size++;
    
    return size;
}

void concatFiles (char *fileName1, char *fileName2)
{
    FILE *f1 = fopen (fileName1, "r+");
    FILE *f2 = fopen (fileName2, "r");

    fseek(f1, 0, SEEK_END);

    int n;
    while (fscanf(f2, "%d", &n) == 1) {
        fprintf(f1, "%d ", n);
    }

    fclose(f1);
    fclose(f2);
}

void kWays (int numberWays) 
{
    int buffer[numberWays];

    for (int i = 0; i<numberWays; i++) {
        char fileName[11] = {'w', 'a', 'y', '0', '0', '0', '.', 't', 'x', 't', '\0'};
        intToChar(i, fileName);

        FILE *way = fopen (fileName, "r");

        fscanf(way, "%d", &buffer[i]);

        fclose(way);

        removeFirstElementFile(fileName);
    } 

    printf("Tico: %d\n", getLesserValue(buffer, numberWays));

    for (int i = 0; i<numberWays; i++) {
        printf("%d ", buffer[i]);
    }

    printf("\n");

    createFileFromArray("buffer.txt", buffer, numberWays);
}

int getLesserValue (int *array, int size)
{
    int aux[size];

    for (int i = 0; i<size; i++) {
        aux[i] = array[i];
    }
    
    sortArray(aux, size);

    return aux[0];
}


void createFileFromArray (char *fileName, int *array, int size)
{
    FILE *file = fopen (fileName, "w");

    for (int i = 0; i<size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);
}

void removeFirstElementFile (char *fileName)
{
    FILE *file = fopen (fileName, "r");
    FILE *fileAux = fopen ("temp.txt", "w");

    int n;
    fscanf(file, "%d", &n);
    while (fscanf(file, "%d", &n) == 1) fprintf(fileAux, "%d ", n);

    fclose(file);
    fclose(fileAux);

    file = fopen (fileName, "w");
    fileAux = fopen ("temp.txt", "r");

    while (fscanf(fileAux, "%d", &n) == 1) fprintf(file, "%d ", n);

    fclose(file);
    fclose(fileAux);

    remove("temp.txt");
}

int main ()
{
    srand(time(NULL));
    int range = 3;
    int numberWays = 3;
    randomFile("randomNumbers.txt", 16);
    createWays(range, numberWays, "testFile.txt");
    kWays(numberWays);

    return 1;
}