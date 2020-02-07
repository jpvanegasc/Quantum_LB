#include"CA_Quantum.hpp"

int main(void){
<<<<<<< HEAD
    Automata QuantumStuffBaby(Lx/2.0, 50);
    std::ofstream result_file1("1.txt");//, result_file2("datos2.txt"), result_file3("datos3.txt");
    int t_max = 100;
=======
    Automata QuantumStuffBaby(1, Lx/2.0, 50);
    std::ofstream result_file1("datos1.txt"), result_file2("datos2.txt"), result_file3("datos3.txt"), result_file4("datos4.txt");
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
    
    for(int t=0; t<t_max; t++){
        QuantumStuffBaby.grafique(t, result_file4);
        QuantumStuffBaby.collision(1);
<<<<<<< HEAD
        QuantumStuffBaby.grafique(t, result_file1);
        result_file1 << '\n';
        //if(t==t_max/2) QuantumStuffBaby.wave(result_file2);
    }
    //QuantumStuffBaby.wave(result_file3);
    
    result_file1.close(); //result_file2.close(); result_file3.close();
=======
        QuantumStuffBaby.advect(1);
        QuantumStuffBaby.collision(0);
        QuantumStuffBaby.advect(0);
        result_file4 << "\n";
        if (t==t_max/2) QuantumStuffBaby.wave(result_file2);
    }
    QuantumStuffBaby.wave(result_file3);
    
    result_file1.close(); result_file2.close(); result_file3.close(); result_file4.close();
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
    return 0;
}