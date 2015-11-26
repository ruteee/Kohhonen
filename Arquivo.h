/*
 * Arquivo.h
 *
 *  Created on: 24 de nov de 2015
 *      Author: ruteee
 */

#ifndef ARQUIVO_H_
#define ARQUIVO_H_
#include <cstring>
#include<iostream>
#include<fstream>

using namespace std;

class Arquivo {
public:
	string arquivo;
	ofstream escritor;
	ifstream leitor;
	double** matriz_de_entradas;
	bool falha;
	int numero_colunas;
	int numero_linhas;


	Arquivo(string arquivo);
	Arquivo();

	void escrever_em_arquivo(ofstream arquivo);

	void ler_do_arquivo();


 

};

#endif /* ARQUIVO_H_ */
