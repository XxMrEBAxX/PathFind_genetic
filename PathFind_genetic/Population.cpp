#include "Population.h"

Population::Population(int popSize, int chromSize, double cRate, double mRate, POSITION startPos, POSITION endPos)
	: m_popSize(popSize), m_chromSize(chromSize), m_crossoverRate(cRate), m_mutationRate(mRate), m_totalFitness(0)
{
	m_startPos = startPos;
	m_endPos = endPos;

	m_population.resize(popSize);
	m_oldPop.resize(popSize);

	for (int i = 0; i < popSize; i++)
		m_population[i].resetChromosome(chromSize, m_startPos, m_endPos);

	evaluation();
	copyPopToOld();
}

Chromosome Population::selection()
{
	int selectIndex = 0;
	double rnd = rand() / (double)RAND_MAX;
	double selRate = 0.0;
	for (int i = 0; i < m_popSize; i++)
	{
		selRate += m_oldPop[i].getFitnessRate();
		if (selRate >= rnd)
		{
			selectIndex = i;
			break;
		}
	}

	return m_oldPop[selectIndex];
}

void Population::crossover(Chromosome& chrom1, Chromosome& chrom2)
{
	int crossPoint = rand() % m_chromSize;
	vector<twobit> genes1 = chrom1.getChromosome();
	vector<twobit> genes2 = chrom2.getChromosome();
	
	for (int i = 0; i < crossPoint; i++)
	{
		swap(genes1[i], genes2[i]);
	}
	chrom1.setChromosome(genes1);
	chrom2.setChromosome(genes2);
}

void Population::mutation(Chromosome& chrom)
{
	double rnd = rand() / (double)RAND_MAX; // double : 0 ~ 1 값
	if (rnd > m_mutationRate)
		return;

	int mutatePoint = rand() % m_chromSize;
	int bitPoint = rand() % 2;
	vector<twobit> genes = chrom.getChromosome();
	genes[mutatePoint].gene ^= 1 << bitPoint; // Flip
	chrom.setChromosome(genes);
}

void Population::evaluation()
{
	m_totalFitness = 0.0;
	int bestChromIndex = 0;
	
	double bestFitness = 0;

	for (int i = 0; i < m_popSize; i++)
	{
		m_population[i].calcFitness();
		double curChromFit = m_population[i].getFitness(); // i번째 크로모좀의 적합도
		if (curChromFit > bestFitness)
		{
			bestChromIndex = i;
			bestFitness = curChromFit;
		}
		m_totalFitness += curChromFit;
	}
	// 각 Chromosome의 FitnessRate 계산
	for (int i = 0; i < m_popSize; i++)
	{
		double curFitRate = m_population[i].getFitness() / m_totalFitness;
		m_population[i].setFitnessRate(curFitRate);
	}
	m_bestChromosome = m_population[bestChromIndex];
}

void Population::copyPopToOld()
{
	for (int i = 0; i < m_popSize; i++)
		m_oldPop[i] = m_population[i];
}

void Population::draw()
{
	for (int i = 0; i < m_popSize; i++)
		m_population[i].draw();
}
