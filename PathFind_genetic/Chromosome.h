#pragma once
#include <vector>
#include <bitset>
#include <math.h>
#include "Position.h"
#include "PacMap.h"
using namespace std;

struct twobit
{
	unsigned int gene : 2;
};

class Chromosome
{
	vector<twobit> m_genes;	// ����ü ��Ʈ��
	POSITION m_startPos;
	POSITION m_endPos;
	POSITION m_curPos;
	PacMap m_pacMap;
	int m_chromSize;
	double m_fitness;	// ���յ�
	double m_fitnessRate;	// 0 ~ 1 ������ ��. ��ü population���� ���յ� ���� ==> population���� ����
public:
	Chromosome(POSITION pos, POSITION pos2, int size = 5) : m_startPos(pos), m_endPos(pos2), m_pacMap(pos2)
	{ 
		resetChromosome(size, pos, pos2);
	};
	Chromosome(int size = 5) : m_startPos(POSITION(0, 0)), m_endPos(POSITION(0, 0)), m_pacMap(POSITION(0, 0))
	{
		resetChromosome(size, POSITION(0, 0), POSITION(0, 0));
	};
	~Chromosome() {}

	void resetChromosome(int size, POSITION pos, POSITION pos2); // ���� �ʱ�ȭ�� ���
	void initChromosome();	// ����ü �ʱ�ȭ

	// getters
	int getChromSize() { return m_chromSize; }
	double getFitness() { return m_fitness; }
	double getFitnessRate() { return m_fitnessRate; }
	vector<twobit> getChromosome() { return m_genes; }
	PacMap getPacMap() { return m_pacMap; }

	// setters
	void setFitnessRate(double fr) { m_fitnessRate = fr; }
	void setChromosome(vector<twobit> genes) { m_genes = genes; }

	void calcFitness();
	void draw();
};

