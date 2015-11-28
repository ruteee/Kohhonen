#include "omp.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "Neuronio.h"
#include "Arquivo.h"
#include "math.h"
#include <locale>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

double* shuffle(double * vetor_to_shuffle, int size){

	srand(time(NULL));
	double* vetor_shuffled= new double[size];
	bool* vetor_flags = new bool[size];
	int nova_posicao;
	
	for(int i = 0; i < size; i++){

		nova_posicao = rand()%size;
		while(vetor_flags[nova_posicao]){
			nova_posicao = rand()%size;
		}
		vetor_shuffled[nova_posicao] = vetor_to_shuffle[i];
		vetor_flags[nova_posicao] = true;

	}

	return vetor_shuffled;
}

int main(){

 double* vet = new double[8];

 for(int i = 0; i < 8; i++)
 	vet[i] = i+1;

 double* vetor_shuffled = shuffle(vet, 8);

  for(int i = 0; i < 8; i++)
 	cout << vetor_shuffled[i]<<endl;


}

