#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WAYS 3
#define SIZE 16

void randomFile (char *fileName, int size);

void randomFile (char *fileName, int size) 
{
    char * aux = (char*)malloc((sizeof(char) * strlen(fileName)) + 5);
    strcpy(aux, fileName);
    strcat(aux, ".txt");

    FILE * file = fopen (aux, "w");

    for (int i = 0; i<size; i++) {
        int n = rand()%100;
        fprintf(file, "%d\n", n);
    }
    
    return;
}

void open_temp(char * arquivo, char ** nome_arquivos, FILE ** arquivos, int tam){
  for (int i = 0; i < (tam + 1); i++){
    // cria nome do arq temporario e abre
    sprintf(nome_arquivos[i],"%s%d.txt", arquivo, i);
    arquivos[i] = fopen(nome_arquivos[i], "w");
  }
}

void close_temp(FILE ** arquivos, int tam){
  for (int i = 0; i < (tam + 1); i++){
    // cria nome do arq temporario e abre
    fclose(arquivos[i]);
  }
}

int fib(int n) 
{ 
    if (n <= 1) 
        return n; 
    return fib(n-1) + fib(n-2); 
}

void get_from_file(char * origem, char ** destino, int caminhos){
    char * aux = (char*)malloc((sizeof(char) * strlen(origem)) + 5);
    strcpy(aux, origem);
    strcat(aux, ".txt");
    
    FILE ** output = (FILE**)malloc(sizeof(FILE*) * (caminhos + 1));
    
    FILE * input = fopen(aux, "r"); 
    open_temp(origem, destino, output, caminhos);


    int n;
    for(int i = 0; i < caminhos; i++){
        
    }

    fclose(input);
    close_temp(output, caminhos);
}

char ** distribution(char * arquivo, int caminhos){
    char ** arquivos = (char**)malloc(sizeof(char*) * (caminhos + 1));

    for(int i = 0; i < caminhos + 1; i++){
        arquivos[i] = (char*)malloc(sizeof(char) * strlen(arquivo) + 5);
    }

    get_from_file(arquivo, arquivos, caminhos);
    return arquivos;
}

void polyphase(char * arquivo, int caminhos){
    char ** arquivos = distribution(arquivo, caminhos);
}

int main() {
    srand(time(NULL));
    char arquivo[] = "randomNumbers";
    randomFile(arquivo, SIZE);
    //polyphase(arquivo, WAYS);
}