#include<iostream>
#include<fstream>

#include"CA_Quantum.hpp"


int main(void){
    Automata QuantumStuffBaby(1);
    int t_max = 100;

    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.grafique(t);
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.collision(1);

        std::cout << "\n";
    }

    return 0;
}