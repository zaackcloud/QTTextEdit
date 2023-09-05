#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,this, &MainWindow::fermetureTab);
    connect(ui->actionOuvrir,&QAction::triggered ,this, &MainWindow::ouvrirFichier);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fichier)
{
    ui->tabWidget->currentIndex();
    if (!fichier.isEmpty()){
        QFile texte(fichier);
        if (texte.open(QIODevice::ReadOnly)){
            QTextStream in(&texte);
            QString contenu = in.readAll();
            texte.close();

            QTextEdit *modif = new QTextEdit;
            modif->setPlainText(contenu);

            ui->tabWidget->addTab(modif, QFileInfo(fichier).fileName());

            connect(modif,&QTextEdit::textChanged,this,&MainWindow::changeTitre);
            ui->tabWidget->setTabsClosable(true);
        }
        else
        {
            qDebug()<<"Erreur d'ouverture du fichier";
        }
    }
}

void MainWindow::saveFile(int tab)
{

}


void MainWindow::ouvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this);
    loadFile(fichier);
    qDebug()<<"fichier selectionné";
}

void MainWindow::fermetureTab(int tab)
{
    QWidget *tabActuelle= ui->tabWidget->widget(tab);
    ui->tabWidget->removeTab(tab);
    qDebug()<<"tab" << tab<< "supprimée";
    delete tabActuelle;

}

void MainWindow::changeTitre()
{
    qDebug()<<"texte modifié";

    int tab=ui->tabWidget->currentIndex();
    if(ui->tabWidget->tabText(tab).endsWith("*")==false)
    {
        ui->tabWidget->setTabText(tab, ui->tabWidget->tabText(tab) + "*");
    }
}




