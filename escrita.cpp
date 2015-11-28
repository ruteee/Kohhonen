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
#include <fstream>
using namespace std;



int main()
{
	ofstream escritor;
	escritor.open("Cores.root");

	escritor << 4096<<endl;
	escritor << 3 <<endl;
	for(int i = 0; i < 16; i++){
		for(int j = 0;  j< 16; j++){
			for(int k= 0; k<16; k++){
				escritor << i*17 << "\t"<< j*17 <<"\t"<< k*17<<endl;
			}
		}
	}
	escritor.close();

}