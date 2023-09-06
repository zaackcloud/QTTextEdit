#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:
    void ouvrirFichier();
    void EnregistrerFichier();
    void fermetureTab(int tab);
    void changeTitre();
    void afficherCurseur();
    void rechercher();
    void remplacer();



private:
    Ui::MainWindow *ui;
    QList<QFile*> currentFile;
    void loadFile(const QString &fichier);
    void saveFile(int tab);


};
#endif // MAINWINDOW_H
