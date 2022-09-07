#include "cast.h"
#include "actor.h"
#include <set>
#include <iostream>
#include <limits>

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
}

bool checkUnionX(set<Actor> x, int l)
{
    set<int> ux;
    for (auto itr = x.begin(); itr != x.end(); ++itr)
    {
        Actor ac = *itr;
        set<int> groups = ac.getGroups();
        ux.insert(groups.begin(), groups.end());
    }

    return ux.size() == l;
}

bool checkUnionXA(set<Actor> x, set<Actor> a, int l)
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

    return uxa.size() == l;
}

int sumValues(set<Actor> x)
{
    int sum = 0;
    for (auto itr = x.begin(); itr != x.end(); ++itr)
    {
        Actor a = *itr;
        sum += a.getValue();
    }

    return sum;
}

int bound()
{
    return numeric_limits<int>::min();
}

void Cast::bb(set<Actor> x, set<Actor> a)
{
    if ((x.size() == this->n) && (checkUnionX(x, this->l)))
    {
        int v = sumValues(x);
        if (v < this->opt)
        {
            this->opt = v;
            this->xopt.clear();
            this->xopt.insert(x.begin(), x.end());
        }
    }
    else if ((x.size() + a.size() >= this->n) && (checkUnionXA(x, a, this->l)))
    {
        int b = bound();
        if (b >= this->opt)
        {
            return;
        }

        auto cl = *a.begin();
        a.erase(a.begin());

        bb(x, a);

        x.insert(cl);
        bb(x, a);
    }
}

void Cast::branchAndBound(bool defLF, bool vblt, bool opt)
{
    set<Actor> a;
    set<Actor> x;
    a.insert(this->a.begin(), this->a.end());
    this->opt = numeric_limits<int>::max();

    this->bb(x, a);

    for (auto itr = this->xopt.begin(); itr != this->xopt.end(); ++itr)
    {
        Actor ac = *itr;
        cout << ac.getId() << " ";
    }
    cout << endl
         << this->opt << endl;
}
