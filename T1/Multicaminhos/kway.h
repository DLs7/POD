// Create k-ways, each one intercalating on the RAM range. Example:
// 3 ways, RAM = 3
// 10 12 14 15 18 10 2 34 20 55 87 92 85 17 - fileName.txt
// First Iteration:
// *The difference between createFirstWays and createWays is that the first sort the groups of numbers on the RAM range.
// way000 - 10 12 14 ->(Sort) 10 12 14 
// way001 - 15 18 10 ->(Sort) 10 15 18 
// way002 - 2 34 20 ->(Sort) 2 20 34
// Second Iteration:
// way000 - 10 12 14 55 87 92
// way001 - 10 15 18 17 85
// way002 - 2 20 34
// Third Iteration:
// fileName.txt is empty, so all the ways were created, end of the function.
void createFirstWays(int numberWays, char* fileName);
void createWays(int numberWays, char* fileName);


// Initialize ways and temp ways with empty values.
void initializeWays(int numberWays);
void initializeTempWays(int numberWays);
void initializeSortedFiles(int numberWays);

// Delete temp ways.
void removeTempWays(int numberWays);

// Delete sorted files.
void removeSortedFiles(int numberWays);

// Function to control all the executions needed for the kWays.
// Step 1: Initialize all the files "wayXXX.txt" with an empty value.
// Step 2: Call the createFirstWays, passing the fileName as the dataFile.
// Step 3: Call the createSortedFile.
// Step 4: Repeat Step 1.
// Step 4: Call the createWays, passing the file created by sortedFile as the dataFile.
void kWays(int numberWays, char* fileName);

// Start the process to create a sortedFile.
// Step 1: Create a k number of tempWayXXX.txt files, initializing it with empty values.
// Step 2: Each temp way will get the first N values from their respectives ways, where N = RAM. 
// The values added to tempWayXXX will get removed from the original way.
// Example:
// RAM = 3, numberWays = 3;
// way000.txt - 24 34 45 11 13 35 11 14 15
// way001.txt - 13 15 43 11 12 32 11
// way002.txt - 11 11 32 11 13 34 
// After calling getNFirsts:
// tempWay000.txt - 24 34 45
// tempWay001.txt - 13 15 43
// tempWay002.txt - 11 11 32
// way000.txt - 11 13 35 11 14 15
// way001.txt - 11 12 32 11
// way002.txt - 11 13 34
// Step 3: Use a buffer to get the first element of each temporary file and then remove it from the tempWayXXX.txt
// Example:
// tempWay000.txt - 24 34 45
// tempWay001.txt - 13 15 43
// tempWay002.txt - 11 11 32
// buffer[RAM] - -1 -1 -1
// After calling the initializeBuffer:
// tempWay000.txt - 34 45
// tempWay001.txt - 15 43
// tempWay002.txt - 11 32
// buffer[RAM] - 24 13 11
// Step 4: Open a new file "fileName.txt" to hold the sorted values.
// Step 5: Call the getLesserValue and store the result on an auxiliary variable called lesserIndex
// Step 6: Store the buffer[lesserIndex] into the sortedFile.
// Step 7: Remove the buffer[lesserIndex] from the buffer and add another value gathered from the same temporaryWay.
// Example:
// tempWay000.txt - 34 45
// tempWay001.txt - 15 43
// tempWay002.txt - 11 32
// buffer[RAM] - 24 13 11
// lesserIndex = 2
// sortedFile.txt - 11
// buffer[RAM] - 24 13 ?
// buffer[RAM] - 24 13 11
// tempWay002.txt - 32
// Repeat Step 5 until the buffer holds only -1 -1 -1 -1 ... RAM.
void createSortedFile(int numberWays, char* fileName);

void normalizeWays(int numberWays);

void printWays(int numberWays);

// Concat two files. Example:
// file1 = 1 2 3
// file2 = 4 5 6
// After concatFiles:
// file1 = 1 2 3 4 5 6
// file2 = 4 5 6
void concatFiles(char* file1Name, char* file2Name);

// Remove the first element of a file.
void removeFirstElement(char *fileName);

// Copy the contents of file2 into file1. Example:
// file1 = 1 2 3
// file2 = 4 5 6
// After copyFile:
// file1 = 4 5 6
// file2 = 4 5 6
void copyFile(char* file1Name, char* file2Name);

// Print the contents of the file on the terminal. Example:
// fileName = "wayXXX.txt"
// wayXXX.txt - 1 2 3 4 5 6
void printFile(char* fileName);

// Returns the index of the lesser value contained inside a buffer, excluding -1.
int getLesserValue(int *buffer);

// Get the first elements of N tempWays, where N = RAM.
void initializeBuffer(int* buffer);

// Set all the contents of the buffer to -1.
void clearBuffer(int* buffer);

// Sort the buffer.
void sortBuffer(int *buffer);

// Print the contents of the buffer on the terminal.
void printBuffer(int *buffer);

// Return True if all the values inside the buffer = -1. 
int checkEmptyBuffer(int *buffer);

// Concat the elements of a buffer and a file. Example:
// fileName - wayXXX.txt
// buffer[3] - 1 2 3
// After the function:
// wayXXX.txt - 1 2 3 
void concatBufferFile(int *buffer, char* fileName);

// Given a number, returns a string with the follow structure: "wayXXX.txt",
// where XXX is the index converted to 3 numbers. Example:
// getWayName(1) = "way001.txt"
// getWayName(999) = "way999.txt"
// The maximum number supported by the function is 999 and the minimum is 0.
void getWayName(int index, char* wayName);

// As getWayName, but it returns a "tempWayXXX.txt"
void getTempWayName(int index, char* tempWayName);

// As getWayName, but ir returns a "sortedFileXXX.txt"
void getSortedFileName(int index, char* sortedFileName);

// Transfer the N first values (where N = RAM) of a wayXXX.txt to its temporary counterpart.
// Example:
// RAM = 3;
// way000.txt = 1 2 3 4 5 6
// After the function:
// tempWay000.txt = 1 2 3
// way000.txt = 4 5 6
void getNFirsts(int numberWays);