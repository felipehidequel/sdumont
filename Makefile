all: 
	mpic++ -Wall -O3 -fopenmp monte_carlo.cpp -o main
clean:
	rm main