#include <iostream>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30;
const int POP_SIZE = 50;   //temporary
const int PRICE[GENE] = { 8, 5, 6, 4, 13, 12, 5, 17, 10, 15, 9, 4, 6, 18, 8, 7, 7, 8, 8, 2, 9, 10, 10, 13, 7, 11, 12, 6, 21, 7 };
const int TIME[GENE] = { 12, 11, 13, 9, 14, 14, 12, 20, 6, 21, 13, 9, 11, 15, 11, 9, 6, 7, 14, 6, 13, 8, 13, 16, 10, 10, 11, 10, 20, 10 };
const float CO_probability = 0.9;
const float MUT_probability = 0.1;
const int MAX_GENERATION = 10;
const int MAX_PRICE = 278;
const int MAX_TIME = 280;
const double TIME_WEIGHTAGE=0.5;
const double PRICE_WEIGHTAGE=0.5;
const double PENALTY_MULTIPLIER = 0.01;
//declare chromosomes data structure
int chromosome[POP_SIZE][GENE];
//declare fitness data structure
double fitness[POP_SIZE];
int parents[2][GENE];
int children[2][GENE];
//declare new data structure to hold new chromosomes
int newChromosomes[POP_SIZE][GENE];
int newChromosomesCounter = 0;

double bestFitness = 0;
double avgFitness = 0.0;
int bestChromosome[GENE];

ofstream bestFitnessFile, avgFitnessFile, bestChromosomeFile;

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
	/*for (int c = 0; c < POP_SIZE; c++) {
		cout << "\tC" << c << "\t";
		for (int i = 0; i < GENE; i++) {
			cout << chromosome[c][i] << " ";
		}
		cout << endl;
	}*/
}

void evaluateChromosome() {
	int accumulatedTime = 0;
	int accumulatedPrice = 0;

	cout << "\tC\t" << "Price\t" << "Time\t" << "Fitness\t" << endl;

	for (int c = 0; c < POP_SIZE; c++) {
		accumulatedTime = 0;
		accumulatedPrice = 0;

		for (int i = 0; i < GENE; i++) {
			if (chromosome[c][i] == 1) {
				accumulatedTime += TIME[i];
				accumulatedPrice += PRICE[i];
			}
		}

		fitness[c] = (((double)accumulatedPrice / MAX_PRICE)*PRICE_WEIGHTAGE)+((1/((double)abs(accumulatedTime-MAX_TIME)+1))*TIME_WEIGHTAGE);

		cout << "\tC" << c << "\t" << accumulatedPrice << "\t" << accumulatedTime << "\t" << fitness[c] << endl;
	}
}

void parentSelection() {
	double totalFitness = 0;
	double pointer[2] = { 0 };
	int indexParents[2];// = { 0 };
	double temp = 0;
	bool p1 = 0; //parent1 is selected flag
	bool p2 = 0; //parent2 is selected flag

	for (int c = 0; c < POP_SIZE; c++) {
		totalFitness += fitness[c];
	}

	do
	{
		pointer[0] = { 0 };
		pointer[1] = { 0 };
		do {
			for (int i = 0; i < 2; i++)
			{
				pointer[i] = 0 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (totalFitness - 0)));
			}
		} while (pointer[0] == pointer[1]);

		temp = 0;
		p1 = 0;
		p2 = 0;

		for (int c = 0; c < POP_SIZE; c++) {
			temp += fitness[c];
			//cout <<c<<" " << temp << endl;

			if (p1 == 1 && p2 == 1)
			{
				break;
			}
			else {
				if (p1 == 0)
				{
					if (temp > pointer[0])
					{
						indexParents[0] = c;
						p1 = 1;
					}
				}
				if (p2 == 0)
				{
					if (temp > pointer[1])
					{
						indexParents[1] = c;
						p2 = 1;
					}
				}
			}
		}

	} while (indexParents[0] == indexParents[1]);

	for (int p = 0; p < 2; p++)
	{
		//cout << "Parent " << p + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			parents[p][g] = chromosome[indexParents[p]][g];
			//cout << " " << parents[p][g];
		}
		//cout << " Fitness= " << fitness[indexParents[p]] << endl;
	}

	/*
		double totalFitness = 0;
		double pointer1 = 0;
		double pointer2 = 0;
		int indexParents[2] = { 0 };
		double temp = 0;
		bool p1 = 0; //parent1 is selected flag
		bool p2 = 0; //parent2 is selected flag
		for (int c = 0; c < POP_SIZE; c++) {
			totalFitness += fitness[c];
		}
		do {
			for (int p = 0; p < 2; p++) {
				do {
					pointer1 = fmod(rand(), totalFitness);
					pointer2 = fmod(rand(), totalFitness);
				} while (pointer1 == pointer2);
			}
			for (int c = 0; c < POP_SIZE; c++) {
				temp += fitness[c];
				if (p1 == 1 && p2 == 1) {
					break;
				}
				else {
					if (temp > pointer1&& p1 == 0) {
						indexParents[0] = c;
						p1 = 1;
					}
					if (temp > pointer2&& p2 == 0) {
						indexParents[1] = c;
						p2 = 1;
					}
				}
			}
		} while (indexParents[0] == indexParents[1]);
		for (int p = 0; p < 2; p++)
		{
			cout << "Parent " << p + 1 << ": ";
			for (int g = 0; g < GENE; g++)
			{
				parents[p][g] = chromosome[indexParents[p]][g];
				cout << " " << parents[p][g];
			}
			cout << " Fitness= " << fitness[indexParents[p]] << endl;
		}
	*/

}

void crossover() {
	float prob = 0;
	int side = 0; //token for coin flip. 0 is heads, 1 is tails

	prob = ((rand() % 10) + 1) / 10.0;

	if (prob < CO_probability) {
		for (int g = 0; g < GENE; g++)
		{
			side = rand() % 2;//0 to children 1, 1 to children 2
			if (side == 0) {
				children[0][g] = parents[0][g];
				children[1][g] = abs(parents[0][g] - 1);
			}
			else {
				children[1][g] = parents[1][g];
				children[0][g] = abs(parents[1][g] - 1);
			}
		}
	}
	else {
		for (int g = 0; g < GENE; g++)
		{
			children[0][g] = parents[0][g];
			children[1][g] = parents[1][g];
		}
		/* cout << "\nCrossover did not happen "; */
	}

	/* for (int c = 0; c < 2; c++)
	{
		cout << "\nChildren" << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
	} */
}

void mutation() {
	float prob = 0;
	int mut_point;
	prob = (rand() % 11) / 10.0;


	for (int c = 0; c < 2; c++)
	{
		if (prob < MUT_probability) {
			mut_point = rand() % GENE;
			//cout << "\nMutation happened for Children " << c + 1 << " at mutation point " << mut_point;
			if (children[c][mut_point] == 0) {
				children[c][mut_point] = 1;
			}
			else {
				children[c][mut_point] = 0;
			}
		}
		else {
			//cout << "\nMutation did not happen for Children " << c + 1;
		}
	}

	/* for (int c = 0; c < 2; c++)
	{
		cout << "\nChildren" << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}

	}
	cout << endl; */
}

void survivalSelection() {
	int candidates[4][GENE];
	int j = 0;

	for (int i = 0; i < 4; i++) {
		if (i < 2) {
			for (int g = 0; g < GENE; g++)
			{
				candidates[i][g] = parents[i][g];
			}
		}
		else {
			for (int g = 0; g < GENE; g++)
			{
				candidates[i][g] = children[j][g];
			}
			j++;
		}
	}

	int accumulatedTime = 0;
	int accumulatedPrice = 0;
	float tempFitness[4];
	float tempBestFitness = 0;
	int bestCandidateIndex[2];
	/* 	int worstChromosomeIndex[2];
		float tempWorstFitness = 100; */

	for (int c = 0; c < 4; c++) {
		accumulatedTime = 0;
		accumulatedPrice = 0;

		for (int i = 0; i < GENE; i++) {
			if (candidates[c][i] == 1) {
				accumulatedTime += TIME[i];
				accumulatedPrice += PRICE[i];
			}
		}

		if (accumulatedTime <= MAX_TIME) {
			tempFitness[c] = accumulatedPrice / (float)MAX_PRICE;
		}
		else {
			tempFitness[c] = accumulatedPrice / (float)MAX_PRICE * PENALTY_MULTIPLIER;
		}
	}

	for (int c = 0; c < 4; c++) {
		if (tempFitness[c] >= tempBestFitness) {
			tempBestFitness = tempFitness[c];
			bestCandidateIndex[0] = c;
		}
	}

	tempBestFitness = 0;

	for (int c = 0; c < 4; c++) {
		if (tempFitness[c] >= tempBestFitness && c != bestCandidateIndex[0]) {
			tempBestFitness = tempFitness[c];
			bestCandidateIndex[1] = c;
		}
	}

	/* 	for (int c = 0; c < POP_SIZE; c++) {
			if (fitness[c] <= tempWorstFitness) {
				tempWorstFitness = fitness[c];
				worstChromosomeIndex[0] = c;
			}
		}
		tempWorstFitness = 100;
		for (int c = 0; c < POP_SIZE; c++) {
			if (fitness[c] <= tempWorstFitness && c != worstChromosomeIndex[0]) {
				tempWorstFitness = fitness[c];
				worstChromosomeIndex[1] = c;
			}
		} */

		/* 	for (int i = 0; i < 2; i++) {
				for (int g = 0; g < GENE; g++) {
					chromosome[worstChromosomeIndex[i]][g] = candidates[bestCandidateIndex[i]][g];
				}
				cout << "Replaced chromosome " << worstChromosomeIndex[i] << " with candidate " << bestCandidateIndex[i] << endl;
			} */
	for (int c = 0; c < 2; c++) {
		for (int g = 0; g < GENE; g++) {
			newChromosomes[newChromosomesCounter][g] = candidates[bestCandidateIndex[c]][g];
		}
		newChromosomesCounter++;
		//cout << "Added new chromosome, counter: " << newChromosomesCounter << endl;
	}
	/*
	for (int p = 0; p < newChromosomesCounter; p++) {
		cout << "\n\t new Chromosomes " << p + 1 << ": ";
		for (int g = 0; g < GENE; g++) {
			cout << newChromosomes[p][g] << " ";
		}
	} 
	cout << endl;*/
}

void copyChromosome() {
	for (int c = 0; c < POP_SIZE; c++)
	{
		for (int g = 0; g < GENE; g++)
		{
			chromosome[c][g] = newChromosomes[c][g];
		}
	}
}

void recordBestFitness() {
	int bestChromosomeIndex;

	for (int c = 0; c < POP_SIZE; c++) {
		if (fitness[c] > bestFitness) {
			bestFitness = fitness[c];

			for (int g = 0; g < GENE; g++) {
				bestChromosome[g] = chromosome[c][g];
			}
		}
	}

	cout << "\n Best Fitness = " << bestFitness;
	cout << "\n Best Chromosome = ";
	for (int g = 0; g < GENE; g++) {
		cout << bestChromosome[g] << " ";
	}
	cout << endl;


	bestFitnessFile << bestFitness << endl;
	for (int g = 0; g < GENE; g++) {
		bestChromosomeFile << bestChromosome[g] << " ";
	}
	bestChromosomeFile << endl;
}

void calcAvgFitness() {
	double sum = 0.0;
	for (int c = 0; c < POP_SIZE; c++) {
		sum += fitness[c]; //sum=sum+fitness
	}
	avgFitness = sum / POP_SIZE;
	cout << "\n Average Fitness = " << avgFitness<<endl;

	avgFitnessFile << avgFitness << endl;
}

int main() {
	srand(time(NULL));

	bestFitnessFile.open("bestFitness.txt");
	avgFitnessFile.open("avgFitness.txt");
	bestChromosomeFile.open("bestChromosome.txt");

	int N;

	cout << "\nENTER NUMBER OF GENERATION: ";
	cin >> N;


	cout << "\nGA START! \n";
	cout << "First generation \n\n";
	cout << "\nINITIALIZATION... \n";

	initializePopulation();

	for (int g = 0; g < N; g++)
	{
		cout << "GENERATION " << g + 1 << endl;

		//cout << "\nPRINT POPULATION \n";
		printChromosome();

		//cout << "\nEVALUATE CHROMOSOME \n";
		evaluateChromosome();
		recordBestFitness();
		calcAvgFitness();

		for (int i = 0; i < POP_SIZE / 2; i++)
		{
			//cout << "\nPARENT SELECTION \n";
			parentSelection();

			//cout << "\nCROSSOVER \n";
			crossover();

			//cout << "\nMUTATION \n";
			mutation();

			//cout << "\nSURVIVAL SELECTION\n";
			survivalSelection();
		}
		copyChromosome();
		printChromosome();
		newChromosomesCounter = 0;
	}

	cout << "\nGA END! \n";

	bestFitnessFile.close();
	avgFitnessFile.close();
	bestChromosomeFile.close();
}
