#include<iostream>
#include<fstream>

#include"Quantum_LG.hpp"

int main(void){
    Automata QuantumStuffBaby(1);
    std::ofstream result_file1("datos1.txt");//, result_file2("datos2.txt");
    int t_max = 100;
    
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.grafique(result_file1, t);
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.collision(1);
    }
    
    result_file1.close();// result_file2.close();
    return 0;
}