/*
 * Arquivo.cpp
 *
 *  Created on: 24 de nov de 2015
 *      Author: ruteee
 */

#include "Arquivo.h"

using namespace std;

Arquivo::Arquivo(string arquivo) {
	this->arquivo = arquivo;
	this-> escritor = escritor(arquivo);
	this-> leitor = leitor(arquivo);

	if(!leitor.is_open()){
		cout<<"Falha ao abrir o arquivo";
		this->falha = true;
	}else{this->falha = false;}
}

void Arquivo::ler_do_arquivo(){


	int numero_colunas;
	int numero_linhas;
	int iterador_linhas= 0;

	leitor >> numero_linhas;
	leitor >> numero_colunas;

	this->numero_colunas = numero_colunas;


	double entradas[numero_colunas];

	this->matriz_de_entradas = new double *[numero_linhas];

	while(iterador_linhas< numero_linhas){

		for(int i = 0; i < numero_colunas; i++)
			leitor >> entradas[i];

		matriz_de_entradas[iterador_linhas] = entradas;
		iterador_linhas++;
	}
}



