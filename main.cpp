#include "mainwindow.h"
#include "sequence.h"
#include "chiffrement.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int tours = 16;
    vector<int> vect = {1, 0, 2};
    srand(time(nullptr));
    Sequence cle("mafalap");
    cle = cle.sous_sequence(0, 53);
    Sequence message(90);
    Sequence alea = message.sous_sequence(0,63);
    vector<int> perm = vect_alea(alea);
    Sequence A = Chiffrer_TDES(message, cle, perm);
    Sequence B = Dechiffrer_TDES(A, cle, perm);

    const string ichemin = "/home/utilisateur/projects/test2/fichier";
    const string ochemin = "/home/utilisateur/projects/test2/fichier chiffrer";
    const string iochemin = "/home/utilisateur/projects/test2/fichier dechiffrer";
    ifstream ifile(ichemin.c_str());
    ofstream ofile(ochemin.c_str());
    ofstream iofile(iochemin.c_str());

    string texte;
    string text;
    string ligne;
    while(getline(ifile, ligne))
    {
        texte += ligne + "\n";
    }


    Sequence c(texte);
    Sequence C = Chiffrer_TDES(c, cle, perm);
    ofile << C.to_texte();
    ofile.close();
    ifstream cfile(ochemin.c_str());
    while(getline(cfile, ligne))
    {
        text += ligne + "\n";
    }

    Sequence crypted(text);
    crypted = crypted.sous_sequence(0, crypted.seque.size()-9);
    Sequence D = Dechiffrer_TDES(crypted, cle, perm);
    cout << int(D.seque==c.seque) << endl;

    iofile << D.to_texte();
    iofile.close();

    MainWindow w(perm);
    w.texte->setText(QString::fromStdString(c.to_texte()));
    w.show();

    return app.exec();
}
