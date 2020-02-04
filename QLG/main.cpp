#include<iostream>
#include<fstream>

#include"Quantum_LG.hpp"

int main(void){
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt"), result_file3("datos3.txt");
    Automata QuantumStuffBaby(Lx/2.0, 50);
    int t_max = 2000;
    
    std::cout << QuantumStuffBaby.mu() << "\n";
    std::cout << QuantumStuffBaby.sigma2() << "\n";

    QuantumStuffBaby.print(result_file1);
    
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.collide(0);
        QuantumStuffBaby.advect();
        QuantumStuffBaby.collide(1);
        QuantumStuffBaby.advect();
        if(t==t_max/2) QuantumStuffBaby.print(result_file2);
    }

    QuantumStuffBaby.print(result_file3);

    result_file1.close(); result_file2.close(); result_file3.close();
    return 0;
}