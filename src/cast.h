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

    void bb(set<Actor> x, set<Actor> a);

public:
    Cast(/* args */);
    //~Cast();
    void branchAndBound(bool defLF, bool vblt, bool opt);
};

#endif