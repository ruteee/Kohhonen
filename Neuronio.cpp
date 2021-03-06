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


Neuronio::Neuronio(){

}

Neuronio::~Neuronio(){

}

void Neuronio::inicializar_vetor_de_pesos(int size){
	this->vetor_de_pesos = new double[size];

	srand(time(NULL));
	for(int i = 0; i<size; i++)
		vetor_de_pesos[i] = (rand()%256);
}

double* Neuronio::get_vetor_de_pesos(){
	return this->vetor_de_pesos;
}

void Neuronio::setLocalizacao(int i, int j){
	this->i = i;
	this->j = j;
}

void Neuronio::setPeso(double peso, int i){
	this->vetor_de_pesos[i] = peso;
}

double Neuronio::getPeso(int i){
	return this->vetor_de_pesos[i];
}

void Neuronio::setDistancia(double distancia){
	this->distancia = distancia;
}

double Neuronio::getDistancia(){
	return this->distancia;
}

int Neuronio::getX(){
	return this->i;
}

int Neuronio::getY(){
	return this->j;
}