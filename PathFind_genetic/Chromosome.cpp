#include "Chromosome.h"

void Chromosome::resetChromosome(int size, POSITION pos, POSITION pos2)
{
	m_chromSize = size;
	m_fitness = 0;
	m_fitnessRate = 0.f;
	m_genes.resize(size);
	m_startPos = pos;
	m_endPos = pos2;
	m_curPos = m_startPos;
	m_pacMap.setEndPos(m_endPos);
	initChromosome();
}

void Chromosome::initChromosome()
{
	int rnd;
	for (int i = 0; i < m_chromSize; i++)
	{
		rnd = rand() % 4;
		m_genes[i].gene = rnd;
	}
	calcFitness();
}

void Chromosome::calcFitness()
{
	m_fitness = 0;
	m_pacMap.InitMap();
	m_curPos = m_startPos;
	m_pacMap.setTile(m_curPos, 3);
	for (int i = 0; i < m_chromSize; i++)
	{
		m_pacMap.Move(m_curPos, m_genes[i].gene);
	}
	// 다 움직이고 나면
	int dx = abs(m_endPos.X - m_curPos.X);
	int dy = abs(m_endPos.Y - m_curPos.Y);

	// fitness function
	m_fitness = 1 / (((double)dx + (double)dy) + 1);
}
#include <iostream>
void Chromosome::draw()
{
	for (auto i : m_genes)
		cout << bitset<2>(i.gene) << " ";
	cout << " ==> " << m_fitness << " : " << m_fitnessRate << endl;
}
