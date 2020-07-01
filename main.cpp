#include <iostream>
#include <ctime>
#include <cmath>
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

		if (accumulatedTime<=MAX_TIME){
			fitness[c]=accumulatedPrice/(float)MAX_PRICE;
		}
		else{
			fitness[c]=accumulatedPrice/(float)MAX_PRICE*0.25; 
		}

		cout << "\tC" << c << "\t" <<accumulatedPrice<<"\t"<< accumulatedTime << "\t" << fitness[c] << endl;
	}
}

void parentSelection(){
	double totalFitness=0;
	double pointer1=0;
	double pointer2=0;
	int indexParents[2];
	double temp=0;
	bool p1=0; //parent1 is selected flag
	bool p2=0; //parent2 is selected flag

	for(int c=0;c<POP_SIZE;c++){
		totalFitness+=fitness[c];
	}

	do{
		do{
			pointer1=fmod(rand(), totalFitness);
			pointer2=fmod(rand(), totalFitness);
		}while(pointer1==pointer2);

		temp=0;

		for(int c=0;c<POP_SIZE;c++){
			temp+=fitness[c];

			if(p1==1&&p2==1){
				break;
			}
			else{
				if (temp>pointer1&&p1==0){
					indexParents[0]=c;
					p1=1;
				}

				if(temp>pointer2&&p2==0){
					indexParents[1]=c;
					p2=1;
				}
			}
		}

	}while(indexParents[0]==indexParents[1]);

	for (int p = 0; p < 2; p++)
	{
		cout << "Parent " << p + 1<<": ";
		for (int g = 0; g < GENE; g++)
		{
			parents[p][g] = chromosome[indexParents[p]][g];
			cout << " " << parents[p][g];
		}
		cout << " Fitness= "<<fitness[indexParents[p]]<<endl;
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
	getchar();
	cout << "\nPARENT SELECTION \n";
	parentSelection();

}
