#ifndef CONNEXION_H
#define CONNEXION_H
#include <QDialog>
#include <cstdio>
#include <iostream>

QT_BEGIN_NAMESPACE
class QTextEdit;
class QMessageBox;
class QLineEdit;
class QPushButton;
class QCheckBox;
QT_END_NAMESPACE

#define TYPE_CONNEXION              1
#define TYPE_GROUPE_CONNEXION       0
#define TYPE_INDETERMINE            -1

#define MODE_EDIT_CONNEXION         1
#define MODE_NEW_CONNEXION          2
#define MODE_NEW_GROUPE             3
#define MODE_EDIT_GROUPE            4


class Connexion: public QDialog
{
public:
    Connexion();
    void setVar(QString varName, QString varValue);
    void setVar(QString varName, int varValue);
    QString getQStringVar(QString varName);
    int getIntVar(QString varName);
    void editConnexion(int mode);
    void displayInfosConnexion();

private slots:
    void saveEditedValues();
    void abandon();

private:
    // variables de definition d'une connexion
    int idConnexion;
    int level;
    QString commentaire;
    int typeItem;       // 0 groupe de connexion ; 1 connexion
    QString groupeConnexionName;
    QString label;
    QString nom;
    QString adresseIP;
    int port;
    bool X11Forwarding;
    QString login;
    QString passwd;
    QString commande;
    bool avecTunnel;
    QString tunnelIP;
    int tunnelPort;
    QString tunnelLogin;
    QString tunnelPassword;
    int tunnelLocalPort;
    QTextEdit *cnxEditZone;

    // variables de fonctionnement
    QWidget *editWidget;

    // zone de texte de la fenetre d'edition
    QLineEdit *editGroupeConnexionName;
    QLineEdit *editNom ;
    QLineEdit *editAdresseIP;
    QLineEdit *editPort;
    QCheckBox *editX11Forwarding;
    QLineEdit *editLogin;
    QLineEdit *editPasswd;
    QLineEdit *editCommande;
    QLineEdit *editAvecTunnel;
    QLineEdit *editTunnelIP;
    QLineEdit *editTunnelPort;
    QLineEdit *editTunnelLogin;
    QLineEdit *editTunnelPassword;
    QLineEdit *editTunnelLocalPort;
    QLineEdit *editCommentaire;
};

#endif // CONNEXION_H
