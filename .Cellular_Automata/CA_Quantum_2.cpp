#include<iostream>
#include<fstream>
#include<cmath>
#include"Random64.h"
using namespace std;

const int Lx = 10;
const int Ly = 10;

class Automata{
	private:
		double juan[Lx][Ly];
	public:
		void inicie(void){
			for (int i=0; i<Lx; i++)
				for (int j=0; j<Ly; j++)
					juan[i][j]=0; 
		}
		void esta_funcion_avanza_un_paso(void);
		void show(void){
			for (int i=0; i<Lx; i++)
				for (int j=0; j<Ly; j++)
					cout << juan[i][j];
			
		}
};



int main(){
	return 0;
}