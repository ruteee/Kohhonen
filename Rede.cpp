#include "omp.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "Neuronio.h"
#include "math.h"
#include <locale>

using namespace std;
int altura, largura;
double distancia;
Neuronio grid_de_neuronios[altura][largura];
string arquivo;
Arquivo arquivo_entrada = new Arquivo(arquivo);

struct Vencedor{
	Neuronio neuronio;

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

	treinamento(
				0.8,
				0,
				0.005,
				100000,
				0.0001,
				altura,
				largura,
				arquivo_entrada.numero_colunas,
				arquivo_entrada.numero_linhas,
				arquivo.matriz_de_entradas);
	
	testeDeRede(0, 0, 255, 2, 2);





}

void treinamento(double sigma,
				double alfa,
				double qsi,
				double epocas,
				double variacao_minima_media,
				int altura_grid,
				int largura_grid,
				int numero_colunas_entrada,
				int numero_linhas_entrada,
				double** matriz_de_entradas){

    int count_epoca = 0;
    double variacao = 0;
    double sigma_k = sigma;
    double alfa_k = alfa;

    do{

    	int count_entradas = 0;

		while(count_entradas < numero_linhas_entrada){
    	/*Parallel begin*/
	    	for(int i = 0; i < altura; i++){
	    		for(int j = 0; j < largura; j++){
	    			distancia =
	    				calcular_distancia_euclidiana(
	    					arquivo_entrada.matriz_de_entradas[i],
							grid_de_neuronios[i][j].vetor_de_pesos,
							arquivo_entrada.numero_colunas
	    					);
	    			grid_de_neuronios[i][j].setDistancia(distancia);
	    		}
	    	}

	    	/*parallel end*/

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


	    	Vencedor vencedor;
			vencedor.neuronio = grid_de_neuronios[menor_index_x][menor_index_y];

		/*parallel begin*/

			
			double** container_de_pesos_antigos = new double*[altura*largura];
			int count_neuronios = 0;

			for(int i = 0; i < altura; i++){
				for(int j = 0; j< largura; j++){
					if(i == vencedor.neuronio.getX() && j == vencedor.neuronio.getY()){

						double* vetor_de_pesos_antigos = new double[numero_colunas_entrada];
							vetor_de_pesos_antigos = grid_de_neuronios[i][j].get_vetor_de_pesos();
							container_de_pesos_antigos[count_neuronios] = vetor_de_pesos_antigos;

						for(int k = 0; k < numero_colunas_entrada; k++){
							//modo vencedor
							grid_de_neuronios[i][j].setPeso(
								grid_de_neuronios[i][j].getPeso(k) + 
								(n*(grid_de_neuronios[i][j].getPeso(k)  - matriz_de_entradas[count_entradas][k]));
						}
					}else{
						container_de_pesos_antigos[count_neuronios] = vetor_de_pesos_antigos;
						for(int k = 0; k < numero_colunas_entrada; k++){
							grid_de_neuronios[i][j].setPeso(
									grid_de_neuronios[i][j].getPeso(k) + 
									(n*funcao_de_vizinhanca(sigma, alfa, vencedor.neuronio, count_epoca, i, j)*
									(grid_de_neuronios[i][j].getPeso(k)  - matriz_de_entradas[count_entradas][k]));
						}
					}
				}
				count_neuronios++;
			}

			count_neuronios = 0;
			double variacao = 0;
			double variacao_media = 0;

			for(int i = 0; i < altura; i++){
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < numero_colunas_entrada; k++){
						varicao += (grid_de_neuronios[i][j].get_vetor_de_pesos())[k] - container_de_pesos_antigos[0][k];
					}
				}
				count_neuronios++;
			}

			variacao_media = variacao/count_neuronios;
			
			count_neuronios = 0;
			variacao_media = 0;


			count_entradas++;
		}
	/*parallel end*/



		alfa_k = 0.9*(1 - count_epoca/epocas);
		sigma_k = sigma*exp(-count_epoca/epocas); 
		count_epoca++;


    }while(count_epoca < epocas && variacao_media > variacao_minima_media);

}


double calcular_distancia_euclidina(double* entrada, double* pesos, int size){

	double distancia = 0;
	for(int i = 0; i < size; i++)
		distancia += pow((pesos[i] - entrada[i]), 2);
	return distancia;
}

double funcao_de_vizinhanca(double sigma, double alfa, Neuronio vencedor, int iteracao, int x_neuronio_atual, int y_neuronio_atual){

	double h;
	double distancia_quadrada;

	distancia_quadrada = pow((neuronio_vencedor.getX() - grid_de_neuronios[x_neuronio_atual][y_neuronio_atual].getX()), 2)+
				pow((neuronio_vencedor.getY() - grid_de_neuronios[x_neuronio_atual][y_neuronio_atual].getY()), 2));
	
	h_site = alfa*exp(-distancia_quadrada/(2*alfa));
	h = exp(distancia_quadrada/(2*sigma);

	return h;

}

void testeDeRede(double R, double G, double B, int num_linhas, int num_colunas){

	double vetor_de_distancias[num_linhas*num_colunas];
	int count_neuronios = 0;
	double entrada[3] = {R, G. B};

	for(int i = 0; i < num_linhas; i++){
		for(int j = 0; j < num_colunas; j++){
			distancia =
				calcular_distancia_euclidiana(entrada[i], grid_de_neuronios[i][j].vetor_de_pesos, 3)
				vetor_de_distancias[count_neuronios] = distancia;
				count_neuronios++;
		}
	}

	double menor_distancia = vetor_de_distancias[0];
	int menor_index_x = 0, menor_index_y = 0;

	for(int i = 0; i < count_neuronios; i++){
		if(vetor_de_distancias[i] < menor_distancia)
			menor_distancia = vetor_de_distancias[i];
			menor_index_x = i/ordem_do_grid;
			menor_index_y = i%ordem_do_grid;
		}
    }

  	
    for(int i = 0; i < ordem_do_grid; i++)
		for(int j = 0; j < ordem_do_grid; j++)
			for(int k = 0; k < 3; k++)
				cout << "Peso "<< k << "do neurônio" << i << j<< (grid_de_neuronios[i][j].get_vetor_de_pesos())[k]<<endl;

	//salvar em arquivo com num linhas, num colunas, vetor_de_pesos;
	// enviar arquivo das entradas 

	cout << endl;

	cout << "Neurônio vencedor: "<< i << ", " << j;

}

