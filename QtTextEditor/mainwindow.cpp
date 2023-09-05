#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOuvrir,&QAction::triggered ,this, &MainWindow::ouvrirFichier);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fichier)
{
    ui->tabWidget->setCurrentIndex(0);
    if (!fichier.isEmpty()){
        QFile texte(fichier);
        if (texte.open(QIODevice::ReadOnly)){
            QTextStream in(&texte);
            QString contenu = in.readAll();
            texte.close();

            QTextEdit *editor = new QTextEdit;
            editor->setPlainText(contenu);

            ui->tabWidget->addTab(editor, QFileInfo(fichier).fileName());
            ui->tabWidget->setTabsClosable(true);

        }
        else
        {
            qDebug()<<"Erreur d'ouverture du fichier";
        }
}
}


void MainWindow::ouvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this);
    loadFile(fichier);
    qDebug()<<"fichier selectionné";
}

