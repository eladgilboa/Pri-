#ifndef INITIALIZED_ARRAY_H
#define INITIALIZED_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
template<typename T>
class InitializedArray
{
private:
    T* vec;
    int* to;
    int* from;
    int top;
    const int length;

protected:
    T default_value;

public:
    InitializedArray( int length, T value = T() );
    //InitializedArray( const InitializedArray<T>& rhs  );
    ~InitializedArray();

    T& operator[](const int index);
    T operator[](const int index) const;
};
/*********************** constructors ****************************/
template<typename T>
InitializedArray<T>::InitializedArray(int len, T value ):top(0),length(len),default_value(value)
{
    vec  = new T[length];
    to   = new int[length];
    from = new int[length];
}

/*********************** destructor ****************************/
template<typename T>
InitializedArray<T>::~InitializedArray()
{
    delete[] vec;
    delete[] to;
    delete[] from;
}
/*********************** operator [] ****************************/
template<typename T>
T& InitializedArray<T>::operator[](const int n)
{
    if (from[n] < top && to[from[n]] == n)
    {
        return vec[n];
    }

    from[n] = top;
    to[top] = n;
    vec[n] = default_value;
    top++;
    return vec[n];
}

template<typename T>
T InitializedArray<T>::operator[](const int n) const
{

    cout << "n= " << n << " " ;
    if (from[n] < top && to[from[n]] == n)
    {
        cout << "vec[n]: "<< vec[n] ;
        return vec[n];
    }
    cout << "default_value: n= "<< n<< " " ;
    return default_value;
}

#endif /* INITIALIZED_ARRAY_H */
