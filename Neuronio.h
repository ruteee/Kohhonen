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

	void setDistancia(double distancia);
	
	void setLocalizacao(int i, int j);

	void setPeso(double peso, int i);

	double getPeso(int i);

	int getX();

	int getY();

	double getDistancia();

};

#endif /* NEURONIO_H_ */
