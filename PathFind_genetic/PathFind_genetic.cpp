#include "Chromosome.h"
#include "Population.h"
#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    /*
        [ 길찾기를 수행하는 유전 알고리즘의 한계 ]
        유전 알고리즘은 우성 형질이 많이 살아남는다는 성질을 가지고 있다.
        즉, 최종 목적지 거리가 가깝게 도달한 크로모좀만 선택될 가능성이 크다.
        이것이 문제이다. 최종 목적지와 가깝게 도달할 경우에서 벽을 만났을 때, 절대 돌아서서 갈 생각을 하지 않는다.
        아무리 돌연변이가 발생한다 한들 벽을 돌아서게 되면 적합도가 낮아지므로 무조건 도태당할 수 밖에 없다.
        따라서 어느 세대를 거쳐도 벽을 돌아서지 않고 계속 벽에서만 부딪히는 세대만이 살아남는다.
    */
    POSITION start = POSITION(13, 29);
    POSITION end = POSITION(12, 1);
    //POSITION start = POSITION(13, 29);
    //POSITION end = POSITION(9, 23);
    //srand((unsigned)time(NULL));
    Population maxone(100, 80, 0.8, 0.02, start, end);

    Chromosome bestChrom = maxone.getBestChromosome();
    double solution = 1;
    double fittest = bestChrom.getFitness();

    // 진화과정
    int generation = 0;
    double crossRate = maxone.getCrossoverRate();

    Chromosome select1(start, end, bestChrom.getChromSize());
    Chromosome select2(start, end, bestChrom.getChromSize());
    while (true)
    {
        generation++;

        cout << "===============" << endl;
        cout << "Generation : " << generation << endl;

        maxone.draw();
        cout << "(Best) ";
        bestChrom.draw();
        bestChrom.getPacMap().DrawMap();

        if (fittest == solution || generation > 1000) break;

        //genetic operator
        int popsize = maxone.getPopSize();
        for (int i = 0; i < popsize; i += 2)
        {
            double rnd = rand() / (double)RAND_MAX; // crossover 수행 여부
            // selection
            select1 = maxone.selection();
            select2 = maxone.selection();
            if (rnd < crossRate) // crossover가 일어나지 않으면 mutation 또한 일어나지 않는다.
            {
                // crossover
                maxone.crossover(select1, select2);
                // mutation
                maxone.mutation(select1);
                maxone.mutation(select2);

                select1.calcFitness();
                select2.calcFitness();
            }
            maxone.pushChromToPop(i, select1);
            maxone.pushChromToPop(i + 1, select2);
        }

        maxone.evaluation();
        maxone.copyPopToOld();

        bestChrom = maxone.getBestChromosome();
        maxone.pushChromToPop(0, bestChrom);

        fittest = bestChrom.getFitness();
    }
    cout << "(Selected Best) ";
    bestChrom.draw();
    bestChrom.getPacMap().DrawMap();

    getchar();
}