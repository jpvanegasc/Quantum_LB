#include<iostream>
#include<fstream>

#include"Quantum_LG.hpp"

int main(void){
<<<<<<< HEAD
    std::ofstream file1("t=0.txt"), file2("t=1000.txt"), file3("t=2000.txt"), file4("4.txt");
    Automata Wave(Lx/2.0, 50);
    int t_max = 400;
    Wave.print(file1);
=======
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt"), result_file3("datos3.txt");
    Automata QuantumStuffBaby(Lx/2.0, 50);
    int t_max = 2000;
    
    std::cout << QuantumStuffBaby.mu() << "\n";
    std::cout << QuantumStuffBaby.sigma2() << "\n";

    QuantumStuffBaby.print(result_file1);
    
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
    for(int t=0; t<t_max; t++){
        Wave.collide(0);
        Wave.advect();
        Wave.collide(1);
        Wave.advect();
        
        if(t==t_max/2) Wave.print(file2);
        file4 << t << '\t' << std::sqrt(Wave.sigma2()) << '\n';
    }
    Wave.print(file3);
    //file4 << std::endl;
    file1.close(); file2.close(); file3.close(); file4.close();
    return 0;
}