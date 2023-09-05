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
    connect(ui->actionOuvrir,SIGNAL(triggered()) ,this,SLOT(ouvrir()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fichier)
{
    qDebug()<<"ouverture en cours";
    QFile texte = fichier;
    QTextStream t(&texte);
    ui->Page->setPlainText(t.readAll());
    qDebug()<<"fichier ouvert";
}

void MainWindow::ouvrir()
{
    QString fichier = QFileDialog::getOpenFileName(this);
    loadFile(fichier);
    qDebug()<<"fichier selectionné";
}

