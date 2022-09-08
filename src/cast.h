#ifndef __CAST__
#define __CAST__

#include <set>
#include "actor.h"

using namespace std;

class Cast
{
private:
    int l;           // S = {1,...,l} -> conjunto de grupos da sociedade
    int m;           // numero de atores
    int n;           // P = {1,...,n} -> conjunto de papeis
    set<Actor> a;    // A = {1,...,m} -> conjunto de atores
    set<Actor> xopt; // conjunto de atores selecionados
    int opt;         // otimo

    bool defFunc; // controle do bb
    bool viabCut;
    bool optCut;

    int nodeCount;
    int64_t duration;

    void bb(set<Actor> x, set<Actor> a);
    int bound(set<Actor> x, set<Actor> a);
    int groupSetUnionX(set<Actor> x);
    int groupSetUnionXA(set<Actor> x, set<Actor> a);

public:
    Cast(/* args */);
    //~Cast();

    void toggleDefaultFunc();
    void toggleViabilityCut();
    void toggleOptimalityCut();
    void branchAndBound();
    void showResults();
};

#endif