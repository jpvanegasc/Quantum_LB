#include<iostream>
#include<fstream>

#include"CA_Quantum.hpp"


int main(void){
    Automata QuantumStuffBaby(1);
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt");
    int t_max = 1e4;
    
    QuantumStuffBaby.wave(result_file1);
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.collision(1);
        //std::cout << "\n";
    }
    QuantumStuffBaby.wave(result_file2);
    
    result_file1.close(); result_file2.close();
    return 0;
}