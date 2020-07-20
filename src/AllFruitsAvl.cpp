#include "AllFruitsAvl.h"
#include<iostream>
#include <vector>
using namespace std;
AllFruitsAvl::AllFruitsAvl():avlTree()
{
    //ctor
}

AllFruitsAvl::~AllFruitsAvl()
{
    //dtor
}

void AllFruitsAvl::getFruitsByRottenBase( avl_node* root, int rottenBase, std::vector<std::shared_ptr<Fruit>>* nodes_array )
{

    if (root == NULL)
        return;

    getFruitsByRottenBase ( root->left, rottenBase, nodes_array );
    if( (root->fruit_ptr->getID() % rottenBase) == 0)
    {
        nodes_array->push_back(root->fruit_ptr);
    }
    getFruitsByRottenBase ( root->right, rottenBase, nodes_array );
};


