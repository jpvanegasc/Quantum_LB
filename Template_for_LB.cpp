const int Lx; // Lattice x size
const int Ly; // Lattice y size

const int Q; // Number of velocity vectors we are using

const double C_general; // Propagation velocity; Written as a constant is used for all lattice

class LatticeBoltzmann{
	private:
		double w[Q];
		/* The f  */
		double f[Lx][Ly][Q], f_new[Lx][Ly][Q]; 
		double C[Lx][Ly]; // C written as function of x and y used when the medium velocity is to be changed
		int V[2][Q]; // V[0][i]=V_ix and V[1][i]=V_iy
	public:
		/**
		 * Load vectors w[Q] and V[2][Q]
		 */
		LatticeBoltzmann(void){

		}
		/**
		 * Macro-Variable: 
		 * @param ix: position on x-axis on which we are calculating
		 * @param iy: position on y-axis on which we are calculating
		 * @param use_new: calculating rho either for f or f_new
		 */
		double rho(int ix, int iy, bool use_new){

		}
		/**
		 * Macro-Variable: Velocity field of the system we are modeling over the x-axis. We define 
		 * f_i(x_0,t) such that the sum over i in the x direction will be U_x(x_0).
		 * @param ix: position on x-axis on which we are calculating
		 * @param iy: position on y-axis on which we are calculating
		 * @param use_new: calculating U_x either for f or f_new
		 */
		double U_x(int ix, int iy, bool use_new){
			
		}
		/**
		 * Macro-Variable: Velocity field of the system we are modeling over the y-axis. We define 
		 * f_i(x_0,t) such that the sum over i in the y direction will be U_y(x_0)
		 * @param ix: position on x-axis on which we are calculating
		 * @param iy: position on y-axis on which we are calculating
		 * @param use_new: calculating U_y either for f or f_new
		 */
		double Uy(int ix, int iy, bool use_new){
			
		}
		/**
		 * Using the LBGK equation and taking d_t/tau as one, f(x_i+d_x,t+d_t) equals this function 
		 * (i.e. f(x_0+d_x,t+d_t)=f_new_i(x_0,t)).
		 * It's defined for the type of system we wish to model (fluids, waves, etc.), and its 
		 * moments are the same as the f(x_i,t) function (i.e. sum over i of f_new_i = sum over i
		 * of f_i). 
		 * @param rho0: macro-variable 
		 * @param U_x0: macro-variable 
		 * @param U_y0: macro-variable 
		 * @param ix:
		 * @param iy:
		 * @param i:
		 */
		double f_eq(double rho0, double U_x0, double U_y0, int ix, int iy, int i){
			
		}
		void colisione(void){
			
		}
		void adveccione(void){
			
		}
		void inicie(double rho0, double Jx0, double Jy0){
			
		}
		void imponer_campos(int t){
			
		}
		
		void imprimase(const char * nombre_archivo);
};