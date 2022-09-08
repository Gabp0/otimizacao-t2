#include "actor.h"
#include <iostream>
#include <list>

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

list<int> Actor::getGroups()
{
    return this->groups;
}

void Actor::addGroup(int g)
{
    this->groups.push_back(g);
}

ostream &operator<<(ostream &os, const Actor &obj)
{
    os << obj.getId() << " => Valor: " << obj.getValue() << " Grupos: " << obj.getGroupSize() << endl;
    return os;
}

bool Actor::operator<(const Actor &obj) const
{
    return (this->id < obj.getId());
}