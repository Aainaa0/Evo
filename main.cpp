//NAME				: AAINAA NABILAH BINTI ROHAIZAD
//MATRIC NO			: B031810373
//SECTION/GROUP		: 2BITI S1G2
//SUBMISSION DATE	: 1/6/2020

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;
//declare constant - problem specification, population size
const int GENE = 8;
const int CAPACITY = 104;
const int POP_SIZE = 10;
const int WEIGHT[GENE] = { 25, 35, 45, 5, 25, 3, 2, 2 };

//declare chromosomes data structure
int chromosome[POP_SIZE][GENE];
//declare fitness data structure
double fitness[POP_SIZE];

int parents[2][GENE];

const float CO_probability = 0.9;

int children[2][GENE];

const float MUT_PROBABILITY = 0.9;

int newChromosome[POP_SIZE][GENE];

int newChromosomeCounter=0;

const int MAX_GENERATION = 100;

double bestFitness = 9.9;
double avgFitness = 0.0;
int bestChromosome[GENE];

ofstream bestFitnessFile, avgFitnessFile, bestChromosomeFile;

void initializePopulation() {
	int randNum;
	//initialize random seed
	srand(time(NULL)); //SOURCE;http://www.cplusplus.com/reference/cstdlib/srand/
	for (int c = 0; c < POP_SIZE; c++) {
		for (int i = 0; i < GENE; i++) {
			randNum = rand() % 2;
			chromosome[c][i] = randNum;
		}
	}
}

/*
rand(): Returns a pseudo-random integral number in the range between 0 and RAND_MAX.
RAND_MAX: This value is library-dependent, but is guaranteed to be at least 32767 on any standard library implementation.
example:
v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014
*/
void printChromosome() {
	for (int c = 0; c < POP_SIZE; c++) {
		cout << "\tC" << c << "\t";
		for (int i = 0; i < GENE; i++) {
			cout << chromosome[c][i] << " ";
		}
		cout << endl;
	}
}
void evaluateChromosome() {
	int accumulatedWeight = 0;
	for (int c = 0; c < POP_SIZE; c++) {
		accumulatedWeight = 0;
		for (int i = 0; i < GENE; i++) {
			if (chromosome[c][i] == 1) {
				accumulatedWeight = accumulatedWeight + WEIGHT[i];
			}
		}
		fitness[c] = abs(CAPACITY - accumulatedWeight) / (float)CAPACITY;
		cout << "\tC" << c << "\tDifference\t" << abs(CAPACITY - accumulatedWeight) << "\tFV\t" << fitness[c] << endl;
	}

}
void parentSelection() {
	int player1, player2;
	int indexParents[2];

	do {
		for (int p = 0; p < 2; p++) {
			player1 = rand() % POP_SIZE;
			do {
				player2 = rand() % POP_SIZE;
			} while (player1 == player2);

			if (fitness[player1] <= fitness[player2]) {
				indexParents[p] = player1;
			}
			else {
				indexParents[p] = player2;
			}
			cout << "\n\t Players: " << player1 << " vs " << player2;
			cout << "\n\t Fitness: " << fitness[player1] << " vs " << fitness[player2];
			cout << "\n\t Winner: " << indexParents[p];
			cout << endl;
		}
	} while (indexParents[0] == indexParents[1]);

	for (int p = 0; p < 2; p++) {
		cout << "\n\t Parents " << p + 1 << " : ";
		for (int g = 0; g < GENE; g++) {
			parents[p][g] = chromosome[indexParents[p]][g];
			cout << parents[p][g]<<" ";
		}
	}

}
void crossover() {
	float prob = 0.0;
	int co_point;

	for (int p = 0; p < 2; p++) {
		for (int g = 0; g < GENE; g++) {
			children[p][g] = parents[p][g];
		}
	}

	prob = ((rand() % 10) + 1) / 10.0;
	if (prob < CO_probability) {
		co_point = rand() % GENE;
		cout << "\n\t Children crossover at " << co_point;
		for (int g = co_point; g < GENE; g++) {
			children[0][g] = parents[1][g];
			children[1][g] = parents[0][g];
		}		
	}
	else {
		cout << "\n\t Crossover did not happen";
	}

	//output
	for (int c = 0; c < 2; c++) {
		cout << "\n\t Children " << c + 1 << ":";
		for (int g = 0; g < GENE; g++) {
			cout << children[c][g]<<" ";
		}
	}
}
void mutation() {
	float prob;
	int mut_point;

	for (int c = 0; c < 2; c++) {
		prob = (rand() % 11) / 10.0;	//generating the prob value
		if (prob < MUT_PROBABILITY) {
			mut_point = rand() % GENE;
			cout << "\n\t Mutation at gene = " << mut_point;
			if (children[c][mut_point] == 0)
				children[c][mut_point] = 1;
			else
				children[c][mut_point] = 0;
		}
		else {
			cout << "\n\t Mutation did not happen.";
		}
	}
	for (int c = 0; c < 2; c++) {
		cout << "\n\tChildren: " << c + 1 << " after mutation: ";
		for (int g = 0; g < GENE; g++) {
			cout << children[c][g] << " ";
		}
	}
}
void survivalSelection() {

	for (int c = 0; c < 2; c++) //copy children to new chromosome
	{ 
		for (int g = 0; g < GENE; g++) 
		{
			newChromosome[newChromosomeCounter][g] = children[c][g];
		}
		newChromosomeCounter++;
	}
	for (int c = 0; c < newChromosomeCounter; c++) //print the new chromosome
	{
		cout << "\n\t New chromosome " << c << " :";
		for (int g = 0; g < GENE; g++)
		{
			cout << newChromosome[c][g] << " ";
		}
	}
}
void copyChromosome() {
	for (int c = 0; c < POP_SIZE; c++)
	{
		for (int g = 0; g < GENE; g++)
		{
			chromosome[c][g] = newChromosome[c][g];
		}
	}
}
void recordBestFitness() {
	for (int c = 0; c < POP_SIZE; c++)
	{
		if (bestFitness > fitness[c])
		{
			bestFitness = fitness[c];
			for (int g = 0; g < GENE; g++)
			{
				bestChromosome[g] = chromosome[c][g];
			}
		}
	}

	//output to console
	cout << "\n Best Fitness = " << bestFitness;
	cout << "\n Best Chromosome = ";
	for (int g = 0; g < GENE; g++)
	{
		cout << bestChromosome[g] << " ";
	}

	//output to file
	bestFitnessFile << bestFitness << endl;
	for (int g = 0; g < GENE; g++)
	{
		bestChromosomeFile << bestChromosome[g] << " ";
	}

	bestChromosomeFile << endl;
}
void calcAvgFitness() {
	double sum = 0.0;
	for (int c = 0; c < POP_SIZE; c++)
	{
		sum += fitness[c];
	}
	avgFitness = sum / POP_SIZE;

	//output to console
	cout << "\n Average Fitness = " << avgFitness;

	//output to console
	avgFitnessFile << avgFitness << endl;
}
int main() {

	bestFitnessFile.open("bestFitness.txt");
	avgFitnessFile.open("avgFitness.txt");
	bestChromosomeFile.open("bestChromosome.txt");

	cout << "\nGA START! \n";

	cout << "\nINITIALIZATION... \n";

	//LAB 3
	initializePopulation();
	//getchar();

	for (int g=0;g<MAX_GENERATION;g++) 
	{
		cout << "GENERATION "<<g+1<<endl;
		//LAB 3
		cout << "\nPRINT POPULATION \n";
		printChromosome();
		//getchar();

		//LAB 4
		cout << "\nEVALUATE CHROMOSOME \n";
		evaluateChromosome();
		recordBestFitness();
		calcAvgFitness();
		//getchar();

		for (int i = 0; i < POP_SIZE / 2; i++)
		{
			cout << "\nPARENT SELECTION \n";
			parentSelection();
			//getchar();

			cout << "\nCROSSOVER \n";
			crossover();
			//getchar();

			cout << "\nMUTATION \n";
			mutation();
			//getchar();

			cout << "\nSURVIVAL SELECTION \n";
			survivalSelection();
			//getchar();
		}
		//for creating new chromosome
		cout << "\nNEW CHROMOSOME COPIED TO CHROMOSOME \n";
		copyChromosome();
		//getchar();
	}
	
	bestFitnessFile.close();
	avgFitnessFile.close();
	bestChromosomeFile.close();

}
