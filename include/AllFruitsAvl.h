#ifndef ALLFRUITSAVL_H
#define ALLFRUITSAVL_H

#include "avl_tree.h"
#include <vector>
class AllFruitsAvl: public avlTree
{
public:
    AllFruitsAvl();
    virtual ~AllFruitsAvl();

    void getFruitsByRottenBase( avl_node* root, int rottenBase, std::vector<std::shared_ptr<Fruit>>* nodes_array );

protected:

private:
};

#endif // ALLFRUITSAVL_H
