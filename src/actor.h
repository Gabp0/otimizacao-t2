#ifndef __ACTOR__
#define __ACTOR__

#include <list>
#include <iostream>
using namespace std;

class Actor
{
private:
    int id;           // identificador do ator
    int v;            // valor cobrado
    int s;            // numero de grupos
    list<int> groups; // indices dos grupos

public:
    Actor(int id, int v, int s);
    // ~Actor();
    int getId() const;
    int getValue() const;
    int getGroupSize() const;
    list<int> getGroups();
    void addGroup(int g);
    bool operator<(const Actor &obj) const;
    friend ostream &operator<<(ostream &os, const Actor &obj);
};

#endif