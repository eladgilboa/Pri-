#ifndef ORCHARD_H
#define ORCHARD_H

#include "Tree.h"
#include "AllFruitsAvl.h"
#include "InitializedArray.h"

class Orchard
{
public:
    Orchard( int _N );
    virtual ~Orchard();

    Tree& operator()( int i, int j );
    Tree  operator()( int i, int j ) const;

    StatusType PlantTree    ( int i, int j );
    StatusType AddFruit     ( int i, int j, int fruitID, int ripeRate );
    StatusType PickFruit    ( int fruitID );
    StatusType RateFruit    ( int fruitID, int ripeRate );
    StatusType GetBestFruit ( int i, int j, int * fruitID );
    StatusType GetAllFruitsByRate ( int i, int j, int ** fruits, int * numOfFruits );
    StatusType UpdateRottenFruits ( int rottenBase, int rottenFactor );


protected:

private:
    int N;
    InitializedArray<Tree*> trees;
    AllFruitsAvl all_fruits_avl;
};

#endif // ORCHARD_H


