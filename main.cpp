#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30;
const int CAPACITY = 104;
const int POP_SIZE = 10;   //temporary
const int PRICE[GENE] = {8, 5, 6, 4, 13, 12, 5, 17, 10, 15, 9, 4, 6, 18, 8, 7, 7, 8, 8, 2, 9, 10, 10, 13, 7, 11, 12, 6, 21, 7};
const int TIME[GENE] = {12, 11, 13, 9, 14, 14, 12, 20, 6, 21, 13, 9, 11, 15, 11, 9, 6, 7, 14, 6, 13, 8, 13, 16, 10, 10, 11, 10, 20, 10};
const float CO_probability = 0.9;
const float MUT_probability = 0.9;
const int MAX_GENERATION = 10;
const int MAX_PRICE=278;
const int MAX_TIME=120;
//declare chromosomes data structure
int chromosome[POP_SIZE][GENE];
//declare fitness data structure
double fitness[POP_SIZE];

int parents[2][GENE];
int children[2][GENE];

void initializePopulation() {
	int randNum;
	
	for (int c = 0; c < POP_SIZE; c++) {
		for (int i = 0; i < GENE; i++) {
			randNum = rand() % 2;
			chromosome[c][i] = randNum;
		}
	}
}

void printChromosome() {
	for (int c = 0; c < POP_SIZE; c++) {
		cout << "\tC" << c << "\t";
		for (int i = 0; i < GENE; i++) {
			cout << chromosome[c][i] << " ";
		}
		cout << endl;
	}
}

void evaluateChromosome(){
	int accumulatedTime=0;
	int accumulatedPrice=0;

	cout << "\tC\t" <<"Price\t"<< "Time\t" << "Fitness\t" << endl;

	for (int c=0;c<POP_SIZE;c++){
		accumulatedTime=0;
		accumulatedPrice=0;

		for(int i=0;i<GENE;i++){
			if (chromosome[c][i]==1){
				accumulatedTime+=TIME[i];
				accumulatedPrice+=PRICE[i];
			}
		}

		if (accumulatedTime<=120){
			fitness[c]=accumulatedPrice/(float)MAX_PRICE;
		}
		else{
			fitness[c]=accumulatedPrice/(float)MAX_PRICE*0.25; 
			//0.25 because with 0.5, over time solution still have better fitness
		}

		cout << "\tC" << c << "\t" <<accumulatedPrice<<"\t"<< accumulatedTime << "\t" << fitness[c] << endl;
	}
}

int main() {
	srand(time(NULL));
	cout << "\nGA START! \n";
	cout << "First generation \n\n";
	cout << "\nINITIALIZATION... \n";

	initializePopulation();
	getchar();

	cout << "\nPRINT INITIAL POPULATION \n";
	printChromosome();
	getchar();
	cout << "\nEVALUATE CHROMOSOME \n";
	evaluateChromosome();

}
