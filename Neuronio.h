/*
 * Neuronio.h
 *
 *  Created on: 23 de nov de 2015
 *      Author: ruteee
 */

#ifndef NEURONIO_H_
#define NEURONIO_H_

class Neuronio {
public:
	Neuronio();
	virtual ~Neuronio();

	double* vetor_de_pesos;
	int i, j;
	double distancia;

	void inicializar_vetor_de_pesos(int size);
	void setDistancia(double distancia){
		this->distancia = distancia;
	}
	void setLocalizacao(int i, int j);

	void setPeso(double peso, int i){
		this->vetor_de_pesos[i] = peso;
	}

	double getPeso(int i){
		return this->vetor_de_pesos[i];
	}

	double getDistancia(){
		return this->distancia;
	}

};

#endif /* NEURONIO_H_ */
