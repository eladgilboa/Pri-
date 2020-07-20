#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Fruit.h"
#include <memory>



struct avl_node
{
    int index;
    std::shared_ptr<Fruit> fruit_ptr;
    struct avl_node* left;
    struct avl_node* right;
};

/*
 * Class Declaration
 */
class avlTree
{
public:
    avlTree() {};
    ~avlTree();

    int height(avl_node* );
    int diff(avl_node* temp);
    avl_node* rr_rotation(avl_node* parent);
    avl_node* ll_rotation(avl_node* parent);
    avl_node* lr_rotation(avl_node* parent);
    avl_node* rl_rotation(avl_node* parent);
    avl_node* balance(avl_node* temp);
    virtual avl_node* find  (avl_node* root, int value);
    virtual avl_node* insert(avl_node* root, int value,std::shared_ptr<Fruit> fruit_ptr);
    virtual avl_node* remove(avl_node* root, int value);
    avl_node* minValueNode(avl_node* root);
    avl_node* maxValueNode(avl_node* root);
    void display(avl_node* ptr, int level);
    int inorder(avl_node* tree, int*, int);
    void clearTree(avl_node*);

    avl_node* root = nullptr;
    int size = 0;

};

#endif // AVL_TREE_H
