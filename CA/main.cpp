#include"CA_Quantum.hpp"


int main(void){
    Automata QuantumStuffBaby(1, Lx/2.0, 50);
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt"), result_file3("datos3.txt"), result_file4("datos4.txt");
    
    QuantumStuffBaby.wave(result_file1);
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.grafique(t, result_file4);
        QuantumStuffBaby.collision(1);
        QuantumStuffBaby.advect(1);
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.advect(0);
        result_file4 << "\n";
        if (t==t_max/2) QuantumStuffBaby.wave(result_file2);
    }
    QuantumStuffBaby.wave(result_file3);
    
    result_file1.close(); result_file2.close(); result_file3.close(); result_file4.close();
    return 0;
}