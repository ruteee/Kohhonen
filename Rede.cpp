#include "omp.h"
#include <cstdio>
#include<cstring>
#include <iostream>
#include "Neuronio.h"
#include "math.h"
#include<locale>

using namespace std;
int altura, largura;
double distancia;
Neuronio grid_de_neuronios[altura][largura];
string arquivo;
Arquivo arquivo_entrada = new Arquivo(arquivo);

struct vencedor{
	int i, j;
	double menor;

};

vencedor neuronio_vencedor;

vencedor vencedores_locais[altura][largura];

void treinamento(double sigma, double qsi, double epocas, double variacap_minima );

void main(int argc[], char* argv[] ){

	setlocale(LC_ALL, "pt_BR.UTF-8");

	int num_threads;

	if(argv[1] == NULL || argv[1] < 0){
		cout<< "Número de threads invalido";
		return;
	}

	num_threads = strtol(argv[1], NULL, 10);

	arquivo = argv[2];

	/*Leitura do arquivo de entradas*/


	if(!arquivo_entrada.falha){
		arquivo_entrada.ler_do_arquivo();
	}else{return;}


	cout << "Insira as dimensões do mapa"<<endl;

	cin  >> altura;
	while(altura < 0){
		cout << "Valor inválido";
		cin  >> altura;
	}

	cin >> largura;
	while(largura < 0){
			cout << "Valor inválido";
			cin  >> largura;
	}


	for(int i = 0; i < altura; i++){
		for(int j = 0; j < largura; j++){
			grid_de_neuronios[i][j] = new Neuronio();
			grid_de_neuronios[i][j].setLocalizacao(i, j);
			grid_de_neuronios[i][j].inicializar_vetor_de_pesos(arquivo_entrada.numero_colunas);
		}
	}





}

void treinamento(double sigma,
				 double qsi,
				 double epocas,
				 double variacao_minima,
				 int altura,
				 int largura){

    int count_epoca = 0;
    double variacao = 0;

    do{
    	/*Parallel begin*/
    	for(int i = 0; i < altura; i++){
    		for(int j = 0; j < largura; j++){
    			distancia =
    				calcular_distancia_euclidina(
    					arquivo_entrada.matriz_de_entradas[i],
						grid_de_neuronios[i][j].vetor_de_pesos,
						arquivo_entrada.numero_colunas
    					);
    			grid_de_neuronios[i][j].setDistancia(distancia);
    		}
    	}

    	double menor_distancia = grid_de_neuronios[0][0].getDistancia();
    	int menor_index_x = 0, menor_index_y = 0;

    	for(int i = 0; i < altura; i++){
    	    for(int j = 0; j < largura; j++){

    	    	if(grid_de_neuronios[i][j].getDistancia() < menor_distancia){
    	    		menor_distancia = grid_de_neuronios[i][j].getDistancia();
    	    		menor_index_x = i;
    	    		menor_index_y = j;
    	    	}
    	    }
    	}


    	vencedor vencedor_local;
		vencedor_local.i = menor_index_x;
		vencedor_local.j = menor_index_y;
		vencedor_local.menor = menor_distancia;

		vencedores_locais[menor_index_x][menor_index_y] = vencedor_local;

		/*parallel end*/

		double menor_dist_global = vencedores_locais[0][0].menor;
		int menor_index_global_x = 0, menor_index_global_y= 0;
		for(int i = 0; i < altura; i++)
			for(int j = 0; j< altura; j++)
				if(vencedores_locais[i][j].menor < menor_dist_global){
					menor_dist_global = vencedores_locais[i][j].menor;
					menor_index_global_x = i;
					menor_index_global_y = j;
				}
		neuronio_vencedor.i = menor_index_global_x;
		neuronio_vencedor.j = menor_index_global_y;

		/*parallel begin*/
		for(int i = 0; i < altura; i++){
			for(int j = 0; j< altura; j++){
				if(i == neuronio_vencedor.i && j == neuronio_vencedor.j){
					//calcula pesos modo vencedor;
				}else{
					//calcula pesos modo perdedor;
				}
			}
		}


    }while(count_epoca > epocas && variacao < variacao_minima);

}


double calcular_distancia_euclidina(double* entrada, double* pesos, int size){

	double distancia = 0;
	for(int i = 0; i < size; i++)
		distancia += pow((pesos[i] - entrada[i]), 2);
	return distancia;
}
