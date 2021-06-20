#include "mainwindow.h"

MainWindow::MainWindow(vector<int> permu)
{
    perm = permu;
    setFixedSize(600, 500);
    QWidget* zoneCentrale = new QWidget;

    QGridLayout *layout = new QGridLayout;
        chemin = new QLineEdit;
        parcourir =  new QPushButton("...");
        QHBoxLayout *groupe_chemin = new QHBoxLayout;
        groupe_chemin->addWidget(chemin);
        groupe_chemin->addWidget(parcourir);

        test = new QLineEdit;

        texte = new QTextEdit;
        QVBoxLayout *box = new QVBoxLayout;
        box->addWidget(texte);
        box->addLayout(groupe_chemin);

        QHBoxLayout *bouton = new QHBoxLayout;
        b_chiffrer = new QPushButton("Chiffrer");
        b_dechiffrer = new QPushButton("Déchiffrer");

        bouton->addWidget(b_chiffrer);
        bouton->addWidget(b_dechiffrer);
        layout->addLayout(bouton, 1, 0);
        layout->addLayout(box, 0, 0);
        layout->addWidget(test, 2, 0, 2, 1);

    zoneCentrale->setLayout(layout);

    setCentralWidget(zoneCentrale);

    chemin->setText("mafalap");

    QObject::connect(b_chiffrer, SIGNAL(clicked()), this, SLOT(chiffrement()));
    QObject::connect(b_dechiffrer, SIGNAL(clicked()), this, SLOT(dechiffrement()));
}

Sequence MainWindow::chiffrement()
{
    Sequence cle = (Sequence((chemin->text().toStdString()))).sous_sequence(0, 53);
    string cstring = (texte->toPlainText()).toStdString();
    Sequence mots(cstring);
    Sequence result = Chiffrer_TDES(mots, cle, perm);
    texte->clear();
    texte->setText(QString::fromStdString(result.to_texte()));
    QString arf = QString::fromStdString(result.to_texte());
    cout << endl << "chiffré prem's  " << result.size() << endl;
    result = Sequence(arf.toStdString());
    cout << endl << "chiffré  " << result.size() << endl;
    return result;
}

Sequence MainWindow::dechiffrement()
{
    Sequence cle = (Sequence((chemin->text().toStdString()))).sous_sequence(0, 53);
    string cstring = (texte->toPlainText()).toStdString();
    Sequence mots(cstring);
    cout << "taille mots " << mots.size() << endl;
    mots = mots.sous_sequence(0, mots.seque.size()-9);
    Sequence result =Dechiffrer_TDES(mots, cle, perm);
    texte->clear();
    texte->setText(QString::fromStdString(result.to_texte()));
    cout << endl << "dechifrré  "  << result.size() << endl;
    return result;
}
