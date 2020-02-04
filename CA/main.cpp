#include"CA_Quantum.hpp"


int main(void){
    Automata QuantumStuffBaby(1, Lx/2.0, 50);
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt"), result_file3("datos3.txt");
    
    QuantumStuffBaby.wave(result_file1);
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.grafique(t, result_file3);
        QuantumStuffBaby.collision(1);
        QuantumStuffBaby.advect();
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.advect();
        result_file3 << "\n";
    }
    QuantumStuffBaby.wave(result_file2);
    
    result_file1.close(); result_file2.close();
    return 0;
}