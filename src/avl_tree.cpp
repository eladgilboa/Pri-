#include<iostream>
#include "avl_tree.h"
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

avlTree::~avlTree()
{
    clearTree(this->root);
}

/*
 * Height of AVL Tree
 */
int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*
 * Height Difference
 */
int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

/*
 * Right- Right Rotation
 */
avl_node* avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
/*
 * Left- Left Rotation
 */
avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

/*
 * Left - Right Rotation
 */
avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

/*
 * Right- Left Rotation
 */
avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}

/*
 * Balancing AVL Tree
 */
avl_node* avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

avl_node* avlTree::find(avl_node* root, int value )
{
    while( root != NULL && root->index != value )
    {
        if( value < root->index)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

avl_node* avlTree::insert(avl_node* root, int value, std::shared_ptr<Fruit> fruit_ptr )
{
    if (root == NULL)
    {
        root = new avl_node;
        root->index = value;
        root->fruit_ptr = fruit_ptr;
        root->left = NULL;
        root->right = NULL;
        this->size++;
        return root;
    }
    else if (value < root->index)
    {
        root->left = insert(root->left, value,fruit_ptr);
        root = balance (root);
    }
    else if (value >= root->index)
    {
        root->right = insert(root->right, value,fruit_ptr);
        root = balance (root);
    }
    return root;
}

avl_node* avlTree::remove(avl_node* root, int value)
{
    if (root == NULL)
        return root;

    if ( value < root->index )
        root->left = remove(root->left, value);

    else if( value > root->index )
        root->right = remove(root->right, value);

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

            // Copy the inorder successor's data to this node
            root->index = temp->index;
            root->fruit_ptr = temp->fruit_ptr;

            // Delete the inorder successor
            root->right = remove(root->right, temp->index);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    root = balance (root);
    return root;
}

avl_node* avlTree::minValueNode(avl_node* root)
{
    avl_node* current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

avl_node* avlTree::maxValueNode(avl_node* root)
{
    avl_node* current = root;

    while (current->right != NULL)
        current = current->right;

    return current;
}

/*
 * Display AVL Tree
 */
void avlTree::display(avl_node* ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level +1 );
        printf("\n");
        if (ptr == root)
            cout<< level <<" Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"    "<<level<<"   ";
        cout<<ptr->index;
        display(ptr->left, ++level);
    }
}

/*
 * return inorder array
 */
int avlTree::inorder(avl_node* root, int* fruit_array, int i)
{
    if (root == NULL)
        return i;

    i = inorder (root->left,fruit_array,i);

    fruit_array[i] = root->fruit_ptr->getID();
    i++;

    i = inorder (root->right,fruit_array,i);
    return i;
}

void avlTree::clearTree(avl_node* root)
{
    if(root != NULL)
    {
        clearTree(root->left);   // Recursively clear the left sub-tree
        clearTree(root->right);   // Recursively clear the right sub-tree
        delete root;         // Delete this node
    }
}
