#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <list>
#include <deque>
#include <vector>
#include <QtWidgets>

using namespace std;

class Sequence
{
    public:
    Sequence();
    Sequence(int);
    Sequence(list<Sequence>);
    Sequence(string);
    int m_size;
    deque<bool> seque;
    deque<bool>::iterator it;
    int size();
    Sequence decalage(int);
    bool &operator[](int);
    bool const operator()(int);
    void operator=(int);
    Sequence operator*(Sequence);
    Sequence permutation(vector<int>);
    Sequence sous_sequence(int, int);
    string to_texte();
    QString afficher();
};

#endif // SEQUENCE_H
