#ifndef MULTITERM_H
#define MULTITERM_H

#include <QDialog>
#include <cstdio>
#include <iostream>

#include "config.h"
#include "connexion.h"

QT_BEGIN_NAMESPACE
//namespace Ui { class MultiTerm; }
class QAction;
class QDialog;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QContextMenuEvent;
class QFile;
QT_END_NAMESPACE



class MultiTerm : public QDialog
{
    Q_OBJECT

public:
    MultiTerm();
    void refreshTreeConnexion();

private slots:
    // fonctions lies aux actions de menus
    void aPropos();
    void quitter();
    void openConnexion();
    void sauvegarderConnexion();
    void sauvegarderSousConnexion();
    void editConfiguration();
    void displayListeConnexions();
    void redrawArbre();

    // fonctions du menu contextuel Connexion
    void contextuelMenu(QPoint);
    void editConnexion();
    void newConnexion();
    void newGroupe();
    void deleteConnexion();
    void lanceConnexion();
    void echangeCleSsh();
    void doubleClicSurConnexion();

    virtual void closeEvent(QCloseEvent*);


private:
    //Ui::MultiTerm *ui;

    Config *multiTermConfig;
    // donnees applicatives
    QString appName = "multiTerm";
    Connexion *connexionCourante;
    QString groupeConnexion;
    Connexion *listeConnexions[200];
    int indexNewConnexion = 0;
    QString connexionFilename;
    QFile *fileCnx;
    QWidget *editWidget;
    bool dataConnexionModifee = false;
    int modeEdition;

    // fonction internes
    void updateTitle(QString filename);
    void lireConfigFile();
    void createActions();
    void createMenus();
    void createArbreCnx();
    void createTabCnx();
    void openListeConnexions(QString filename);
    void sauvegardeFichierConnexion(QString filename);
    void ecritLigne(QString ligne, int nbTab);
    void displayInfosConnexion(Connexion *cnx);
    void creeConnexion();
    void editItem(int mode);

    // architectures des layout
    QGroupBox *arbreCnxGroupBox;
    QGroupBox *tabCnxGroupBox;
    QTreeWidget *arbreDesConnexions;
    QTreeWidgetItem *doubleClicConnexion;
    //QTabWidget *tabConnexions;
    QTextEdit *editTab;

    // menus application
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuAide;
    // menu contextuel connexion
    QMenu *menuCtxConnexion;

    // actions de menu
    QAction *actionAPropos;
    QAction *actionQuitter;
    QAction *actionOuvrir;
    QAction *actionSauvegarder;
    QAction *actionSauvegarderSous;
    QAction *actionEditConfiguration;
    QAction *actionListeConnexions;
    QAction *actionRedrawArbre;
    // actions de menu contexttuel
    QAction *actionNewGroupe;
    QAction *actionContextuelMenu;
    QAction *actionEditConnexion;
    QAction *actionNewConnexion;
    QAction *actionDeleteConnexion;
    QAction *actionLanceConnexion;
    QAction *actionEchangeCleSsh;




};
#endif // MULTITERM_H
