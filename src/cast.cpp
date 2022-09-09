#include "cast.h"
#include "actor.h"
#include "quicksort.h"
#include <set>
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

int Cast::groupSetUnionX(list<Actor> x)
// faz a uniao dos grupos dos conjuntos de atores X
{
    int b[this->l];
    int bSize = 0;

    for (Actor itr : x)
    {
        Actor ac = itr;
        set<int> groups = ac.getGroups();
        for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
        {
            int g = *itr2;
            int i;

            for (i = 0; i < bSize; i++)
            {
                if (g == b[i])
                    break;
            }
            if (i == bSize)
            {
                b[bSize] = g;
                bSize++;
            }
        }
    }
    return bSize;
}

int Cast::groupSetUnionXA(list<Actor> x, list<Actor> a)
// faz a uniao dos grupos dos conjuntos de atores X
{
    int b[this->l];
    int bSize = 0;

    for (Actor itr : x)
    {
        Actor ac = itr;
        set<int> groups = ac.getGroups();
        for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
        {
            int g = *itr2;
            int i;

            for (i = 0; i < bSize; i++)
            {
                if (g == b[i])
                    break;
            }
            if (i == bSize)
            {
                b[bSize] = g;
                bSize++;
            }
        }
    }
    for (Actor itr : a)
    {
        Actor ac = itr;
        set<int> groups = ac.getGroups();
        for (auto itr2 = groups.begin(); itr2 != groups.end(); ++itr2)
        {
            int g = *itr2;
            int i;

            for (i = 0; i < bSize; i++)
            {
                if (g == b[i])
                    break;
            }
            if (i == bSize)
            {
                b[bSize] = g;
                bSize++;
            }
        }
    }
    return bSize;
}

int sumValues(list<Actor> x)
// soma o valor de um conjunto de atores
{
    int sum = 0;
    for (Actor itr : x)
    {
        Actor a = itr;
        sum += a.getValue();
    }

    return sum;
}

int minValue(list<Actor> x)
{
    int min = numeric_limits<int>::min();
    for (Actor itr : x)
    {
        Actor ac = itr;
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
        double gulosoSum = 0;
        // cout << aSize << " " << this->n - x.size() << "\n";
        auto it = a.begin();

        for (int i = 0; i < this->n - x.size() && i < a.size(); i++, ++it)
        {
            gulosoSum += it->getValue() / it->getGroupSize();
        }
        return sumValues(x) + gulosoSum;
    }

    return sumValues(x) + (this->n - x.size()) * minValue(a);
}

void Cast::bb(list<Actor> x, list<Actor> a)
{
    if ((x.size() == this->n) && (groupSetUnionX(x) == this->l))
    { // folha da arvore

        int v = sumValues(x);
        if (v < this->opt)
        { // testa se é melhor que o otimo
            this->opt = v;
            this->xopt = list(x);
        }
    }
    else if (a.size() == 0)
    {
        return;
    }
    else
    {
        if (this->viabCut && (!(x.size() + a.size() >= this->n) || !(groupSetUnionXA(x, a) == this->l)))
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

            auto cl = *a.begin();
            a.erase(a.begin());

            this->nodeCount++;
            bb(x, a); // nao contem o elemento

            this->nodeCount++;
            x.push_back(cl);
            bb(x, a); // contem o elemento

            return;
        }
    }
}

bool compareValue(const Actor &first, const Actor &second)
{
    // return ((first.getValue() / first.getGroupSize()) > (second.getValue() / second.getGroupSize()));
    return ((first.getValue()) < (second.getValue()));
}

bool compareId(const Actor &first, const Actor &second)
{
    return (first.getId() < second.getId());
}

void Cast::branchAndBound()
{
    list<Actor> a(this->a);
    list<Actor> x; // atores escolhidos

    a.sort(compareValue);

    this->opt = numeric_limits<int>::max(); // otimo
    this->nodeCount = 0;                    // numero de nodos

    auto start = chrono::high_resolution_clock::now();
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
        this->xopt.sort(compareId);
        for (Actor ac : this->xopt)
        {
            cout << ac.getId() << " ";
        }
        cout << endl;
        cout << this->opt << endl;
    }

    cerr << "Tempo: " << this->duration << " microsegundos" << endl;
    cerr << "Nodes: " << this->nodeCount << endl;
}