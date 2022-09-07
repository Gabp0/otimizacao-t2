#ifndef __ACTOR__
#define __ACTOR__

#include <set>
#include <iostream>
using namespace std;

class Actor
{
private:
    int id;          // identificador do ator
    int v;           // valor cobrado
    int s;           // numero de grupos
    set<int> groups; // indices dos grupos

public:
    Actor(int id, int v, int s);
    // ~Actor();
    int getId() const;
    int getValue() const;
    int getGroupSize() const;
    set<int> getGroups();
    void addGroup(int g);
    bool operator<(const Actor &obj) const;
    friend ostream &operator<<(ostream &os, const Actor &obj);
};

#endif