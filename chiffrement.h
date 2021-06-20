#ifndef CHIFFREMENT_H
#define CHIFFREMENT_H

#include "sequence.h"
#include <algorithm>
#include <QString>
#include <QChar>

using namespace std;

vector<int> reciproque(vector<int> permutation);
Sequence sous_cle(Sequence cle1, Sequence cle2, int n);
Sequence chiffrer(Sequence message, Sequence cle, vector<int> perm, int tours);
Sequence dechiffrer(Sequence message, Sequence cle, vector<int> perm, int tours);
vector<int> vect_alea(Sequence message);
Sequence Chiffrer_TDES(Sequence message, Sequence cle, vector<int> perm);
Sequence Dechiffrer_TDES(Sequence message, Sequence cle, vector<int> perm);



#endif // CHIFFREMENT_H
