#pragma once
#include "Chromosome.h"

class Population
{
	vector<Chromosome> m_population;	// current generation
	vector<Chromosome> m_oldPop;		// parent generation

	POSITION m_startPos;
	POSITION m_endPos;

	Chromosome m_bestChromosome;

	int m_popSize;
	int m_chromSize;

	double m_crossoverRate;
	double m_mutationRate;

	double m_totalFitness;		// ��� fitness ���� ���� ��
public:
	Population(int popSize, int chromSize, double cRate, double mRate, POSITION startPos, POSITION endPos);
	~Population() {}

	// genetic algorithm ������
	Chromosome selection();
	void crossover(Chromosome& gene1, Chromosome& gene2);
	void mutation(Chromosome& gene);
	void evaluation();

	// getter
	Chromosome getBestChromosome() { return m_bestChromosome; }
	int getPopSize() { return m_popSize; }
	int getChromSize() { return m_chromSize; }
	double getCrossoverRate() { return m_crossoverRate; }
	double getMutationRate() { return m_mutationRate; }

	// setter
	
	// extra function
	void copyPopToOld(); // ���� ���븦 �θ� ����� �����
	void pushChromToPop(int pos, Chromosome chrom) // ���� ���
	{
		m_population[pos] = chrom;
	}
	void draw();
};

