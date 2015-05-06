
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
using namespace std;


int main(){
	const int N = 100; // Size of square grid
	int timesteps = 20000; // Self-explanatory
	int Ntemps = 401; // Number of temperatures used

	double T; // Temperature: T=1/beta (k=1)

	int spins[N][N]; // Matrix containing spin orientations (+1,-1)
	double Ho, Hf; // Hamiltonian before and after proposed change
	int suma;	// Sum variable, for storing sum of all spins
	double M[timesteps]={}; // Mean magnetization of the system as a function of 'time'
	double Mmean, var, sd; // Mean of M over last values
	int nx, ny; // Position indices for the grid


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Random seed, needed for seeing equal likelihood of getting +1/-1 at low T
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int> distribution_bin(0,1); // Binary random number, will be converted later to +1/-1
  std::uniform_int_distribution<int> distribution_grid(0,N-1); // Random generation of grid position indices
  std::uniform_real_distribution<double> distribution_real(0.0,1.0); // Random number compared to probability of accepting unfavorable change

	std::ofstream output_Mmean("Mmean.txt");
for (int cont=0; cont<Ntemps; cont++){
T=1 + cont*0.005;
cout << "T = " << T << endl;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			spins[i][j] = -1 + 2*distribution_bin(generator); // Randomly initialize spins
		}
	} 

	for (int t=0; t<timesteps; t++){

		for (int i=0; i<(N*N); i++){
			// Initialize hamiltonians sum
			Ho = 0;
			Hf = 0;

			// Get random position in the grid
			nx = distribution_grid(generator); 
			ny = distribution_grid(generator);

			// Sum all contributions to original and possible new hamiltonians, being careful of borders
			if (nx > 0){
				Ho = Ho - spins[nx][ny]*spins[nx-1][ny];
				Hf = Hf + spins[nx][ny]*spins[nx-1][ny];	
			}
			if (nx < N-1){
				Ho = Ho - spins[nx][ny]*spins[nx+1][ny];
				Hf = Hf + spins[nx][ny]*spins[nx+1][ny];	
			}
			if (ny > 0){
				Ho = Ho - spins[nx][ny]*spins[nx][ny-1];
				Hf = Hf + spins[nx][ny]*spins[nx][ny-1];	
			}
			if (ny < N-1){
				Ho = Ho - spins[nx][ny]*spins[nx][ny+1];
				Hf = Hf + spins[nx][ny]*spins[nx][ny+1];	
			}

			// Apply spin inversion according to conditions
			if (  (Hf<Ho) || ( distribution_real(generator) < exp(-(Hf-Ho)/T) )  ){
				spins[nx][ny] = -spins[nx][ny];
			}

		}
		// Sum all spins in the matrix
		suma=0;
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				suma += spins[i][j];
			}
		}
		M[t] = double(suma)/N/N; // Get mean magnetization for this 'time'
	}

/*
// open files for final spin matrix and M(t)
	std::ofstream output_spins("spins.txt");
	std::ofstream output_M("magnet.txt");
*/
/*
// Write both
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			output_spins << spins[i][j] << " ";
		}
		output_spins << "\n";
	}
	
	for (int t=0; t<timesteps; t++){
		output_M << M[t] << "\n";
	}
*/
	Mmean=0;
	var=0;
	for (int t=timesteps/2; t<timesteps; t++){
		Mmean+=M[t]/(timesteps/2);
	}
	for (int t=timesteps/2; t<timesteps; t++){
		var+=(M[t]-Mmean)*(M[t]-Mmean);
	}
	var/=(timesteps/2 -1);
	sd=sqrt(var);
	output_Mmean << T << " " << Mmean << " " << sd << "\n";
}

	return 0;
}
