#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "chiffrement.h"
#include <vector>
#include <string>
#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(vector<int> perm);
    QTextEdit *texte;
    QLineEdit *chemin;
    QLineEdit *test;
    QPushButton *parcourir;
    QPushButton *b_chiffrer;
    QPushButton *b_dechiffrer;
    vector<int> perm;

public slots:
    Sequence chiffrement();
    Sequence dechiffrement();
};

#endif // MAINWINDOW_H
