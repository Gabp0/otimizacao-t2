#include "cast.h"
#include "actor.h"
#include <set>
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

        this->a.insert(aux);
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

set<int> groupSetUnionX(set<Actor> x)
// faz a uniao dos grupos dos conjuntos de atores X, entao compara com S
{
    set<int> ux;
    for (auto itr = x.begin(); itr != x.end(); ++itr)
    {
        Actor ac = *itr;
        set<int> groups = ac.getGroups();
        ux.insert(groups.begin(), groups.end());
    }

    return ux;
}

set<int> groupSetUnionXA(set<Actor> x, set<Actor> a)
// faz a uniao dos grupos dos conjuntos de atores X e A, entao compara com S
{
    set<int> uxa;

    for (auto itr = x.begin(); itr != x.end(); ++itr)
    {
        Actor ac = *itr;
        set<int> groups = ac.getGroups();
        uxa.insert(groups.begin(), groups.end());
    }

    for (auto itr = a.begin(); itr != a.end(); ++itr)
    {
        Actor ac = *itr;
        set<int> groups = ac.getGroups();
        uxa.insert(groups.begin(), groups.end());
    }

    return uxa;
}

int sumValues(set<Actor> x)
// soma o valor de um conjunto de atores
{
    int sum = 0;
    for (auto itr = x.begin(); itr != x.end(); ++itr)
    {
        Actor a = *itr;
        sum += a.getValue();
    }

    return sum;
}

int bound(bool defaultFunction)
// funcao limitante
{
    return numeric_limits<int>::min();
}

void Cast::bb(set<Actor> x, set<Actor> a)
{
    if ((x.size() == this->n) && (groupSetUnionX(x).size() == this->l))
    { // folha da arvore

        int v = sumValues(x);
        if (v < this->opt)
        { // testa se é melhor que o otimo
            this->opt = v;
            this->xopt.clear();
            this->xopt.insert(x.begin(), x.end());
        }
    }
    else if (a.size() == 0)
    {
        return;
    }
    else
    {
        if (this->viabCut && (!(x.size() + a.size() >= this->n) || !(groupSetUnionXA(x, a).size() == this->l)))
        { // corte por viabilidade
            cout << "cortando por viabilidade" << endl;
            return;
        }
        else
        {
            int b = bound(this->defFunc);
            if (this->optCut && (b >= this->opt))
            { // corte por otimalidade
                return;
            }

            auto cl = *a.begin();
            a.erase(a.begin());

            this->nodeCount++;
            bb(x, a); // nao contem o elemento

            x.insert(cl);
            this->nodeCount++;
            bb(x, a); // contem o elemento

            return;
        }
    }
}

void Cast::branchAndBound()
{
    set<Actor> a;
    a.insert(this->a.begin(), this->a.end()); // atores que podem ser escolhidos

    set<Actor> x; // atores escolhidos

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