#include "library1.h"
#include "Tree.h"
#include "AllFruitsAvl.h"
#include "Orchard.h"
#include "Fruit.h"


using namespace std;

Orchard::Orchard(int _N):N(_N),trees(_N*_N,nullptr)
{

}

Orchard::~Orchard()
{

}

Tree& Orchard::operator()(int i, int j)
{
    return *trees[i * N + j];
}

Tree Orchard::operator()(int i, int j) const
{
    return *trees[i * N + j];
}

StatusType Orchard::PlantTree    ( int i, int j )
{
    if( i > N-1 || i < 0 || j > N-1 || j < 0 )
    {
        return StatusType::INVALID_INPUT;
    }

    int treeIndex = i * N + j;
    if( trees[treeIndex] != nullptr)
        return StatusType::FAILURE;

    trees[i * N + j] = new Tree();
    return StatusType::SUCCESS;
};

StatusType Orchard::AddFruit( int i, int j, int fruitID, int ripeRate )
{
    if( i > N-1 || i < 0 || j > N-1 || j < 0 || fruitID <=0 || ripeRate <= 0)
        return StatusType::INVALID_INPUT;

    int treeIndex = i * N + j;

    if( trees[treeIndex] == nullptr)// tree does not exist
        return StatusType::FAILURE;

    if( all_fruits_avl.find( all_fruits_avl.root, fruitID) != NULL )// fruit exist
        return StatusType::FAILURE;

    std::shared_ptr<Fruit> fruit = std::make_shared<Fruit>(fruitID,ripeRate,treeIndex);


    all_fruits_avl.root = all_fruits_avl.insert( all_fruits_avl.root, fruitID, fruit);
    trees[i * N + j]->root = trees[treeIndex]->insert( trees[treeIndex]->root, ripeRate, fruit);

    return StatusType::SUCCESS;
};

StatusType Orchard::PickFruit ( int fruitID )
{
    if(fruitID <= 0)
        return StatusType::INVALID_INPUT;

    avl_node* node = all_fruits_avl.find( all_fruits_avl.root, fruitID);

    if( node == NULL )
        return StatusType::FAILURE;

    all_fruits_avl.root = all_fruits_avl.remove( all_fruits_avl.root, fruitID);

    int treeIndex = node->fruit_ptr->getTreeIndex();
    trees[treeIndex]->root = trees[treeIndex]->remove( trees[treeIndex]->root, node->fruit_ptr->getRipeRate(), fruitID);

    return StatusType::SUCCESS;
};

StatusType Orchard::RateFruit( int fruitID, int ripeRate )
{
    if(fruitID <= 0 || ripeRate <= 0)
        return StatusType::INVALID_INPUT;

    // if fruit does not exist
    avl_node* node = all_fruits_avl.find( all_fruits_avl.root, fruitID);
    if( node == NULL)
        return StatusType::FAILURE;


    std::shared_ptr<Fruit> fruit = node->fruit_ptr;
    int treeIndex = fruit->getTreeIndex();

    trees[treeIndex]->root = trees[treeIndex]->remove( trees[treeIndex]->root, fruit->getRipeRate(), fruit->getID() );
    fruit->setRipeRate( ripeRate );
    trees[treeIndex]->root = trees[treeIndex]->insert( trees[treeIndex]->root, fruit->getRipeRate(), fruit);

    return StatusType::SUCCESS;
}

StatusType Orchard::GetBestFruit ( int i, int j, int * fruitID )
{
    if( i > N-1 || i < 0 || j > N-1 || j < 0 || fruitID == NULL )
        return StatusType::INVALID_INPUT;

    if( trees[i*N+j] == nullptr)// tree does not exist
        return StatusType::FAILURE;

    if(trees[i*N+j]->best_fruit_ptr == NULL)
    {
        *fruitID = -1;
    }
    else
    {
        *fruitID = trees[i*N+j]->best_fruit_ptr->getID();
    }

    return StatusType::SUCCESS;
};

StatusType Orchard::GetAllFruitsByRate ( int i, int j, int** fruits, int* numOfFruits )
{
    if( i > N-1 || i < 0 || j > N-1 || j < 0 )
        return StatusType::INVALID_INPUT;

    int treeIndex = i * N + j;

    if( trees[treeIndex] == nullptr)
        return StatusType::FAILURE;

    *numOfFruits = trees[treeIndex]->size;

    if(numOfFruits == 0)
    {
        fruits = nullptr;
    }
    else
    {
        int * fruit_array = (int*)malloc( sizeof(int) * trees[treeIndex]->size );

        if( fruit_array == NULL)
            return StatusType::ALLOCATION_ERROR;

        trees[i * N + j]->inorder(trees[treeIndex]->root, fruit_array, 0 );
        *fruits = fruit_array;
    }

    return StatusType::SUCCESS;
};

StatusType Orchard::UpdateRottenFruits ( int rottenBase, int rottenFactor )
{
    if( rottenBase < 1 || rottenFactor < 1   )
        return StatusType::INVALID_INPUT;


    std::vector<shared_ptr<Fruit>> fruit_ptrs_array ;

    all_fruits_avl.getFruitsByRottenBase( all_fruits_avl.root, rottenBase, &fruit_ptrs_array );

    for( unsigned int i=0; i < fruit_ptrs_array.size(); ++i)
    {
        std::shared_ptr<Fruit> fruit = fruit_ptrs_array[i];
        int treeIndex = fruit->getTreeIndex();
        int ripeRate  = fruit->getRipeRate();
        int id        = fruit->getID();

        trees[treeIndex]->root = trees[treeIndex]->remove( trees[treeIndex]->root, ripeRate, id );
        fruit->setRipeRate( ripeRate * rottenFactor );
        trees[treeIndex]->root = trees[treeIndex]->insert( trees[treeIndex]->root, fruit->getRipeRate(), fruit);
    }

    return StatusType::SUCCESS;
};

