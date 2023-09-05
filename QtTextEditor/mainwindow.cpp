#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,this, &MainWindow::fermetureTab);
    connect(ui->actionOuvrir,&QAction::triggered ,this, &MainWindow::ouvrirFichier);
    connect(ui->actionEnregistrer,&QAction::triggered,this,&MainWindow::EnregistrerFichier);

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
        if (texte.open(QIODevice::ReadWrite)){
            QTextStream in(&texte);
            QString contenu = in.readAll();
            this->currentFile.append(&texte);
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
    qDebug()<<"enregistrement en cours";
    QTextEdit *modif = qobject_cast<QTextEdit*>(ui->tabWidget->widget(tab));
    QFile *fichier=this->currentFile.at(tab);
    if(fichier->open(QFile::ReadWrite | QFile::Text)){
        QTextStream sortie(fichier);
        sortie<<modif->toPlainText();
        fichier->close();
    }


}


void MainWindow::ouvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this);
    loadFile(fichier);
    qDebug()<<"fichier selectionné";
}

void MainWindow::EnregistrerFichier()
{
    saveFile(ui->tabWidget->currentIndex());
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




