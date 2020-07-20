#ifndef TREE_H
#define TREE_H

#include "avl_tree.h"

class Tree : public avlTree
{
public:
    Tree();
    virtual ~Tree();

    avl_node* insert(avl_node*, int, std::shared_ptr<Fruit> fruit_ptr) override;
    avl_node* remove(avl_node*, int, int );

    std::shared_ptr<Fruit> best_fruit_ptr;

protected:

private:
};

#endif // TREE_H
