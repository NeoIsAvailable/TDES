#include "chiffrement.h"
#include <QChar>

using namespace std;

vector<int> reciproque(vector<int> permutation)
{
    vector<int> result(permutation.size());
    for(uint i=0; i<result.size(); i++)
    {
        result[permutation[i]]=i;
    }
    return result;
}

Sequence sous_cle(Sequence cle1, Sequence cle2, int n)
{
    cle1.decalage(n);
    cle2.decalage(n);

    return Sequence({cle1.sous_sequence(0, 15), cle2.sous_sequence(0, 15)});
}

Sequence chiffrer(Sequence message, Sequence cle, vector<int> perm, int tours)
{
    Sequence result=message.permutation(perm);
    for(int i=0; i<tours; i++)
    {
        Sequence bloc1=result.sous_sequence(0, result.seque.size()/2-1);
        Sequence bloc2=result.sous_sequence((result.seque.size()/2), result.seque.size()-1);
        Sequence ss_cle=sous_cle(cle.sous_sequence(i,i+15), cle.sous_sequence(i+16,i+31), i%2+1);
        bloc1 = bloc1*ss_cle;
        result = Sequence({bloc2, bloc1});
    }
    return result.permutation(reciproque(perm));
}

Sequence dechiffrer(Sequence message, Sequence cle, vector<int> perm, int tours)
{
    Sequence result=message.permutation(perm);
    for(int i=0; i<tours; i++)
    {
        Sequence bloc1=result.sous_sequence(0,result.seque.size()/2-1);
        Sequence bloc2=result.sous_sequence(result.seque.size()/2, result.seque.size()-1);;
        Sequence ss_cle=sous_cle(cle.sous_sequence(tours-1-i,tours-1-i+15), cle.sous_sequence(tours-1-i+16,tours-1-i+31), (tours-1-i)%2+1);
        bloc2 = bloc2*ss_cle;
        result = Sequence({bloc2, bloc1});
    }
    result = result.permutation(reciproque(perm));
    return result;
}

vector<int> vect_alea(Sequence message)
{
    int i=0;
    vector<int> perm;
    int x = rand()%message.seque.size();
    perm.push_back(rand()%message.seque.size());
    while(perm.size()<message.seque.size())
    {
        x = rand()%message.seque.size();
        if( (x==0 && (perm[0]!=0) && (i==0)) || (!(*find(perm.begin(), perm.end(), x)==x)) )
        {
            perm.push_back(x);
            if(x==0){i++;}
        }
    }
    return perm;
}

Sequence Chiffrer_TDES(Sequence message, Sequence cle, vector<int> perm)
{
    Sequence mess = message;
    while(mess.seque.size()%64!=0)
    {
        mess.seque.push_back(0);
    }
    list<Sequence> result;
    for (uint pos=0 ; pos<mess.seque.size()-1 ; pos+= 64)
    {
        Sequence ss_result = mess.sous_sequence(pos, pos+63);
        for(int k=0; k<3 ; k++)
        {
            ss_result = chiffrer(ss_result, cle, perm, 16);
        }
        result.push_back(ss_result);
    }

    return Sequence(result);
}

Sequence Dechiffrer_TDES(Sequence message, Sequence cle, vector<int> perm)
{
    list<Sequence> list_result;
    for (uint pos=0 ; pos<message.seque.size()-1 ; pos+=64)
    {
        Sequence ss_result = message.sous_sequence(pos, pos+63);
        for(int k=0; k<3; k++)
        {
            ss_result = dechiffrer(ss_result, cle, perm, 16);
        }
        list_result.push_back(ss_result);
    }

    Sequence result(list_result);
    int taille = result.seque.size();
    bool non_null = result[taille-1] + result[taille-2] + result[taille-3] + result[taille-4] + result[taille-5] + result[taille-6] + result[taille-7] + result[taille-8];
    while(!non_null)
    {
        taille = result.seque.size();
        for(int i=0 ; i<8 ; i++) {result.seque.pop_back();}
        non_null += result[taille-9] + result[taille-10] + result[taille-11] + result[taille-12] + result[taille-13] + result[taille-14] + result[taille-15] + result[taille-16];
    }

    return result;
}
