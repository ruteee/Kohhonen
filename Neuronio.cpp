/*
 * Neuronio.cpp
 *
 *  Created on: 23 de nov de 2015
 *      Author: ruteee
 */

#include "Neuronio.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void Neuronio::inicializar_vetor_de_pesos(int size){
	this->vetor_de_pesos = new double[size];

	srand(time(NULL));
	for(int i = 0; i<size; i++)
		vetor_de_pesos[i] = (rand()/10)%1;
}

void Neuronio::setLocalizacao(int i, int j){
	this->i = i;
	this->j = j;
}

