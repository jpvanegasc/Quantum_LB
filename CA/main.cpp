#include<iostream>
#include<fstream>

#include"CA_Quantum.hpp"

int main(void){
    Automata QuantumStuffBaby(Lx/2.0, 50);
    std::ofstream result_file1("1.txt");//, result_file2("datos2.txt"), result_file3("datos3.txt");
    int t_max = 100;
    
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.collision(1);
        QuantumStuffBaby.grafique(t, result_file1);
        result_file1 << '\n';
        //if(t==t_max/2) QuantumStuffBaby.wave(result_file2);
    }
    //QuantumStuffBaby.wave(result_file3);
    
    result_file1.close(); //result_file2.close(); result_file3.close();
    return 0;
}