
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>
using namespace std;


int main(){
	const int N = 100;
	int timesteps = 10000;

	double T;

	int spins[N][N];
	double Hf, Ho;
	int suma;	
	double M[timesteps]={};

	int nx, ny;


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int> distribution_bin(0,1);
  std::uniform_int_distribution<int> distribution_grid(0,N-1);
  std::uniform_real_distribution<double> distribution_real(0.0,1.0);


	cout <<"Dame el valor de kT" << endl;
  cin >> T;

	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			spins[i][j] = -1 + 2*distribution_bin(generator);
		}
	} 

	for (int t=0; t<timesteps; t++){

		for (int i=0; i<(N*N); i++){
			Ho = 0;
			Hf = 0;
			nx = distribution_grid(generator);
			ny = distribution_grid(generator);

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

			if (  (Hf<Ho) || ( distribution_real(generator) < exp(-(Hf-Ho)/T) )  ){
				spins[nx][ny] = -spins[nx][ny];
			}

		}

		suma=0;
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				suma += spins[i][j];
			}
		}
		M[t] = double(suma)/N/N;
	}


// open the file (for writing because it is an ofstream, meaning "output file stream")
	std::ofstream output_spins("spins.txt");
	std::ofstream output_M("magnet.txt");

	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			output_spins << spins[i][j] << " "; // behaves like cout - cout is also a stream
		}
		output_spins << "\n";
	}
	
	for (int t=0; t<timesteps; t++){
		output_M << M[t] << "\n"; // behaves like cout - cout is also a stream
	}

	return 0;
}
