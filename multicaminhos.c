#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Error handling messages
void errorMessage (int errorCode)
{
    char* errorMessage;

    switch (errorCode) {
        case 1:
            errorMessage = "Unable to create file.\n";
            break;
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
    char fileName[9] = {'w', 'a', 'y', 'i', '.', 't', 'x', 't', '\0'};
    for (int i = 0; i < numberFiles; i++) {
        fileName[3] = i+48;
        createFile(fileName);
    }

    return 1;
}

// Generate a file with random numbers.
void randomFile (char *fileName, int size) 
{
    return;
}

int main ()
{
    int numberWays = 10;
    createFiles(numberWays);



    return 1;
}