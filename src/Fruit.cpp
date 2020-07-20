#include "Fruit.h"

const int Fruit::getID() const
{
    return this->ID;
}

const int Fruit::getRipeRate() const
{
    return this->ripeRate;
}

void Fruit::setRipeRate( int newRipeRate )
{
    this->ripeRate = newRipeRate;
}

const int Fruit::getTreeIndex() const
{
    return this->treeIndex;
}
