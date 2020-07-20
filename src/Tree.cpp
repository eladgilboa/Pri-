#include "avl_tree.h"
#include "Tree.h"
#include <iostream>
using namespace std;
Tree::Tree():avlTree()
{

}

Tree::~Tree()
{
    //dtor
}

avl_node* Tree::insert(avl_node* root, int rate, std::shared_ptr<Fruit> fruit_ptr )
{
    if (root == NULL)
    {
        //check if the new one is best fruit
        if( best_fruit_ptr== nullptr || rate < best_fruit_ptr->getRipeRate() || ( rate == best_fruit_ptr->getRipeRate() && fruit_ptr->getID() < best_fruit_ptr->getID() ) )
        {
            best_fruit_ptr = fruit_ptr;
        }
        root = new avl_node;
        root->index = rate;
        root->fruit_ptr = fruit_ptr;
        root->left = NULL;
        root->right = NULL;
        this->size++;
        return root;
    }
    else if (rate < root->index)
    {
        root->left = insert(root->left, rate,fruit_ptr);
        root = balance (root);
    }
    else if (rate > root->index)
    {
        root->right = insert(root->right, rate,fruit_ptr);
        root = balance (root);
    }
    else if (rate == root->index)
    {
        if( fruit_ptr->getID() < root->fruit_ptr->getID() )
        {
            root->left = insert(root->left, rate,fruit_ptr);
            root = balance (root);
        }
        else if ( fruit_ptr->getID() > root->fruit_ptr->getID() )
        {
            root->right = insert(root->right, rate,fruit_ptr);
            root = balance (root);
        }
    }
    return root;
}

avl_node* Tree::remove(avl_node* root, int rate, int id)
{
    if(root == NULL)
    {
        return root;
    }

    if( rate < root->index )
        root->left = remove(root->left, rate, id);

    else if( rate > root->index )
        root->right = remove(root->right, rate, id);

    else if( id < root->fruit_ptr->getID() )
        root->left = remove(root->left, rate, id);

    else if( id > root->fruit_ptr->getID() )
    {
        root->right = remove(root->right, rate, id);
    }
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {

            avl_node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                // One child case
                *root = *temp;// Copy the contents of the non-empty child
            }

            this->size--;
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            avl_node* temp = minValueNode(root->right);

            root->index = temp->index;
            root->fruit_ptr = temp->fruit_ptr;

            // Delete the inorder successor
            root->right = remove(root->right, temp->index, temp->fruit_ptr->getID() );
        }
    }

    // If the tree had only one node then return
    if (root == NULL){
        return root;
    }

    root = balance (root);
    best_fruit_ptr = minValueNode(root)->fruit_ptr;
    return root;
}

