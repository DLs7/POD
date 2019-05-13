#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick.h"

#define TAM 20

static int obtem_pivo(int *vet, int esq, int dir){
  //return(vet[esq]);//primeiro
  //return(vet[dir]);//ultimo
  return(vet[(esq+dir)/2]);//meio
}

void quicksort(int * vet, int esq, int dir) {
    int pivo = obtem_pivo(vet, esq, dir);
    int i = esq;
    int j = dir - 1;
    while (i <= j){
        while(vet[i] < pivo && i < dir) 
            i++;
        while(vet[j] > pivo && j > esq)
            j--;
        
        if(i <= j){
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }

    }

    if(j > esq)
        quicksort(vet, esq, j + 1); 
    if(i < dir)
       quicksort(vet, i, dir);
    }