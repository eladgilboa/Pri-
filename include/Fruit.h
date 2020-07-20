#ifndef FRUIT_H
#define FRUIT_H


class Fruit
{
public:
    Fruit(int _ID, int _ripeRate, int _treeIndex ):ID(_ID),ripeRate(_ripeRate),treeIndex(_treeIndex) {};
    virtual ~Fruit() {};

    const int getID() const;

    const int getRipeRate() const;
    void setRipeRate( int newRipeRate );

    const int getTreeIndex() const;

protected:

private:
    const int ID;
    int ripeRate;
    const int treeIndex;
};

#endif // FRUIT_H
