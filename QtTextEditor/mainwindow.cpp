#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


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
    connect(ui->actionRechercher,&QAction::triggered, this, &MainWindow::rechercher);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fichier)
{
    ui->tabWidget->currentIndex();
    if (!fichier.isEmpty()){
        QFile *texte=new QFile(fichier);
        if (texte->open(QIODevice::ReadWrite)){
            QTextStream in(texte);
            QString contenu = in.readAll();
            this->currentFile.append(texte);
            texte->close();

            QTextEdit *modif = new QTextEdit;
            modif->setPlainText(contenu);

            ui->tabWidget->addTab(modif, QFileInfo(fichier).fileName());

            connect(modif,&QTextEdit::textChanged,this,&MainWindow::changeTitre);
            connect(modif,&QTextEdit::cursorPositionChanged,this,&MainWindow::afficherCurseur);
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
    if(fichier->open(QFile::WriteOnly | QFile::Text)){
        QTextStream sortie(fichier);
        sortie<<modif->toPlainText();
        fichier->close();
    }
    QString nom= ui->tabWidget->tabText(tab);
    nom.chop(1);
    ui->tabWidget->setTabText(tab,nom);


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

void MainWindow::afficherCurseur()
{
    int ligne,colonne;
    QTextEdit *modif = qobject_cast<QTextEdit*>(ui->tabWidget->currentWidget());
    QTextCursor curseur=modif->textCursor();
    ligne=curseur.blockNumber();
    colonne=curseur.columnNumber();

    ui->statusbar->showMessage(tr("position %1 : %2").arg(ligne).arg(colonne));
}

void MainWindow::rechercher()
{
    QTextEdit *modif = qobject_cast<QTextEdit*>(ui->tabWidget->currentWidget());
    QString text = QInputDialog::getText(this, tr("Rechercher"), tr("Entrez le texte à rechercher:"));
    modif->moveCursor(QTextCursor::Start);
    QTextCursor chercher = modif->document()->find(text, modif->textCursor(), QTextDocument::FindWholeWords);
        if(chercher.isNull()) {
            QMessageBox::information(this, tr("Rechercher"), tr("L'expression \"%1\" n'apparaît pas dans le texte").arg(text));
        } else {
            modif->setTextCursor(chercher);
        }
}




