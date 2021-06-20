#include "sequence.h"
#include <bitset>
#include <iostream>

Sequence::Sequence()
{
    m_size=4;
    bool bit = 0;
     for (int i=0; i<m_size ; i++)
    {
        bit = rand()%2;
        seque.push_back(bit);
    }
}

Sequence::Sequence(int n)
{
    m_size=n;
    bool bit = 0;
     for (int i=0; i<m_size; i++)
    {
        bit = rand()%2;
        seque.push_back(bit);
    }
}

Sequence::Sequence(list<Sequence> seq)
{
    list<Sequence>::iterator i1=seq.begin();
    for(i1=seq.begin(); i1!=seq.end(); i1++)
    {
        Sequence X = *i1;
        for(int i=0; i<X.m_size; i++)
        {
            seque.push_back(X.seque[i]);
        }
    }
}

Sequence::Sequence(string texte)
{
    for(char i : texte)
        {
            bitset<8> octet = bitset<8>(i);
            for(int k=7; k>=0 ; k--)
            {
                seque.push_back(octet[k]);
            }
        }
}

int Sequence::size()
{
    return seque.size();
}

bool &Sequence::operator[](int n)
{
    return seque[n];
}

bool const Sequence::operator()(int n)
{
    return seque[n];
}

void Sequence::operator=(int n)
{
    seque.clear();
    int i=0;
    while(i<m_size)
    {
        seque.push_front(n%2);
        n=n/2;
        i++;
    }
    return;
}

Sequence Sequence::decalage(int n)
{
    deque<bool> copie = seque;
    Sequence result;
    for(int i=0; i<seque.size(); i++)
    {
        result.seque[i]=copie[(i+n)%seque.size()];
    }
    return result;
}

Sequence Sequence::operator*(Sequence seq1)
{
    Sequence result(seq1.seque.size());
    result.seque.clear();
    for(int i=0; i<seq1.seque.size(); i++)
    {
        result.seque.push_back(seque[i]^seq1[i]);
    }
    return result;
}

Sequence Sequence::permutation(vector<int> vect)
{
    Sequence result(vect.size());
    for(int i=0; i<result.seque.size(); i++)
    {
        result[vect[i]]=seque[i];
    }
    return result;
}

Sequence Sequence::sous_sequence(int i1, int i2)
{
    Sequence result(i2-i1+1);
    int i=i1;
    for(i; i<=i2; i++)
    {
        result[i-i1]=seque[i];
    }
    return result;
}

string Sequence::to_texte()
{
    string texte;
    for(int i=0 ; i<seque.size(); i++)
    {
        bitset<8> octet(0);
        for (int pos=0; pos<8 ; pos++)
        {
            bool bit = seque[i];
            octet.set(7-pos, bit);
            i++;
        }
        i--;
        texte += char(octet.to_ulong());
    }

    return texte;
}

QString Sequence::afficher()
{
    QString sequence;
    for(int i=0; i!=seque.size(); i++)
    {
        sequence += QString::number(seque[i]);
    }
    return sequence;
}
