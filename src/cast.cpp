#include "cast.h"
#include "actor.h"
#include "quicksort.h"
#include <list>
#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

Cast::Cast()
{
    cin >> this->l >> this->m >> this->n;

    for (size_t i = 0; i < this->m; i++)
    {
        int v, s;
        cin >> v >> s;

        Actor aux(i + 1, v, s);

        for (size_t j = 0; j < s; j++)
        {
            int g;
            cin >> g;
            aux.addGroup(g);
        }

        this->a.push_back(aux);
    }

    this->defFunc = true;
    this->viabCut = true;
    this->optCut = true;
}

void Cast::toggleDefaultFunc()
{
    this->defFunc = !this->defFunc;
}

void Cast::toggleViabilityCut()
{
    this->viabCut = !this->viabCut;
}

void Cast::toggleOptimalityCut()
{
    this->optCut = !this->optCut;
}

int Cast::grouplistUnionX(list<Actor> x)
// faz a uniao dos grupos dos conjuntos de atores X
{
    // int b[this->l];
    // int bSize = 0;

    // for (auto itr = x.begin(); itr != x.end(); ++itr)
    // {
    //     Actor ac = *itr;
    //     list<int> groups = ac.getGroups();
    //     for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
    //     {
    //         int g = *itr2;
    //         int i;

    //         for (i = 0; i < bSize; i++)
    //         {
    //             if (g == b[i])
    //                 break;
    //         }
    //         if (i == bSize)
    //         {
    //             b[bSize] = g;
    //             bSize++;
    //         }
    //     }
    // }
    // return bSize;

    list<int> ux;
    list<int> group;
    for (Actor g : x)
    {
        group = g.getGroups();
        ux.insert(ux.end(), group.begin(), group.end());
    }
    ux.sort();
    ux.unique();

    return ux.size();
}

int Cast::grouplistUnionXA(list<Actor> x, list<Actor> a)
// faz a uniao dos grupos dos conjuntos de atores X
{
    // int b[this->l];
    // int bSize = 0;

    // for (auto itr = x.begin(); itr != x.end(); ++itr)
    // {
    //     Actor ac = *itr;
    //     list<int> groups = ac.getGroups();
    //     for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
    //     {
    //         int g = *itr2;
    //         int i;

    //         for (i = 0; i < bSize; i++)
    //         {
    //             if (g == b[i])
    //                 break;
    //         }
    //         if (i == bSize)
    //         {
    //             b[bSize] = g;
    //             bSize++;
    //         }
    //     }
    // }
    // for (auto itr = a.begin(); itr != a.end(); ++itr)
    // {
    //     Actor ac = *itr;
    //     list<int> groups = ac.getGroups();
    //     for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
    //     {
    //         int g = *itr2;
    //         int i;

    //         for (i = 0; i < bSize; i++)
    //         {
    //             if (g == b[i])
    //                 break;
    //         }
    //         if (i == bSize)
    //         {
    //             b[bSize] = g;
    //             bSize++;
    //         }
    //     }
    // }
    // return bSize;

    list<int> uxa;
    list<int> group;
    for (Actor g : x)
    {
        group = g.getGroups();
        uxa.insert(uxa.end(), group.begin(), group.end());
    }
    for (Actor g : a)
    {
        group = g.getGroups();
        uxa.insert(uxa.end(), group.begin(), group.end());
    }

    uxa.sort();
    uxa.unique();

    return uxa.size();
}

int sumValues(list<Actor> x)
// soma o valor de um conjunto de atores
{
    int sum = 0;
    for (Actor ac : x)
    {
        sum += ac.getValue();
    }

    return sum;
}

int minValue(list<Actor> x)
{
    int min = numeric_limits<int>::min();
    for (Actor ac : x)
    {
        if (ac.getValue() < min)
            min = ac.getValue();
    }

    return min;
}

int Cast::bound(list<Actor> x, list<Actor> a)
// funcao limitante
{
    if (this->defFunc)
    {
        // int aSize = a.size();
        // double b[aSize];
        // int i = 0;
        // for (auto itr = a.begin(); itr != a.end(); ++itr)
        // {
        //     Actor ac = *itr;
        //     b[i] = ac.getValue() / ac.getGroupSize();
        // }
        // quickSort(b, 0, aSize);

        // double gulosoSum = 0;
        // // cout << aSize << " " << this->n - x.size() << "\n";

        // for (int i = 0; i < this->n - x.size() && i < aSize; i++)
        // {
        //     gulosoSum += b[i];
        // }
        // return sumValues(x) + gulosoSum;

        // return numeric_limits<int>::min();

        int greedySum = 0;
        int remainingSize = this->n - x.size();
        list<Actor> aux(a);
        for (size_t i = 0; i < remainingSize; i++)
        {
            greedySum += aux.front().getValue();
            aux.pop_front();
        }

        return sumValues(x) + greedySum;
    }

    return sumValues(x) + (this->n - x.size()) * minValue(a);
}

void Cast::bb(list<Actor> x, list<Actor> a)
{
    if ((x.size() == this->n) && (grouplistUnionX(x) == this->l))
    { // folha da arvore

        int v = sumValues(x);

        if (v < this->opt)
        { // testa se é melhor que o otimo
            this->opt = v;
            this->xopt.~list();
           
            this->xopt = list(x);
        }
    }
    else if (a.size() == 0)
    {
        return;
    }
    else
    {

        if (this->viabCut && (!(x.size() + a.size() >= this->n) || !(grouplistUnionXA(x, a) == this->l)))
        { // corte por viabilidade
            return;
        }
        else
        {
            int b = bound(x, a);
            if (this->optCut && (b >= this->opt))
            { // corte por otimalidade
                return;
            }

            Actor ac = a.front();
            a.pop_front();

            this->nodeCount++;
            bb(x, a); // nao contem o elemento

            this->nodeCount++;
            x.push_back(ac);
            bb(x, a); // contem o elemento

            return;
        }
    }
}

bool compare(const Actor &first, const Actor &second)
{
    return ((first.getValue() / first.getGroupSize()) < (second.getValue() / second.getGroupSize()));
}

void Cast::branchAndBound()
{
    list<Actor> a(this->a); // atores que podem ser escolhidos
    list<Actor> x;          // atores escolhidos

    this->opt = numeric_limits<int>::max(); // otimo
    this->nodeCount = 0;                    // numero de nodos

    auto start = chrono::high_resolution_clock::now();
    a.sort(compare);
    this->bb(x, a); // chamada do branch and bound
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    this->duration = duration.count();
}

void Cast::showResults()
{
    if (this->opt == numeric_limits<int>::max())
    {
        cout << "Inviável" << endl;
    }
    else
    {
        for (auto itr = this->xopt.begin(); itr != this->xopt.end(); ++itr)
        {
            Actor ac = *itr;
            cout << ac.getId() << " ";
        }
        cout << endl;
        cout << this->opt << endl;
    }

    cerr << "Tempo: " << this->duration << " microsegundos" << endl;
    cerr << "Nodes: " << this->nodeCount << endl;
}