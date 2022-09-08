#include "actor.h"
#include <iostream>
#include <set>

using namespace std;

Actor::Actor(int id, int v, int s)
{
    this->id = id;
    this->s = s;
    this->v = v;
}

int Actor::getId() const
{
    return this->id;
}

int Actor::getValue() const
{
    return this->v;
}

int Actor::getGroupSize() const
{
    return this->s;
}

set<int> Actor::getGroups()
{
    return this->groups;
}

void Actor::addGroup(int g)
{
    this->groups.insert(g);
}

ostream &operator<<(ostream &os, const Actor &obj)
{
    os << obj.getId() << " => Valor: " << obj.getValue() << " Grupos: " << obj.getGroupSize() << endl;
    return os;
}

bool Actor::operator<(const Actor &obj) const
{
    return (this->v < obj.getValue());
}