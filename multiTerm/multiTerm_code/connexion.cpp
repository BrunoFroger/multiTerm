
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QCheckBox>

#include "connexion.h"
#include "config.h"

//--------------------------------------------
//
//      Connexion::Connexion
//
//--------------------------------------------
Connexion::Connexion()
{
    this->idConnexion = -1;
    this->level = -1;
    this->commentaire = "";
    this-> typeItem = TYPE_INDETERMINE;
    this->groupeConnexionName = "";
    this->label = "";
    this->nom = "";
    this->adresseIP = "";
    this->X11Forwarding = false;
    this->login = "";
    this->passwd = "";
    this->commande = "";
    this->avecTunnel = false;
    this->tunnelIP = "";
    this->tunnelPort = 22;
    this->tunnelLogin = "";
    this->tunnelPassword = "";
    this->tunnelLocalPort = 10022;
}

//--------------------------------------------
//
//      Connexion::setVar
//
//--------------------------------------------
void Connexion::setVar(QString varName, int varValue){
    if (varName.compare("idConnexion") == 0){
        this->idConnexion = varValue;
    } else if (varName.compare("level") == 0){
        this->level = varValue;
    } else if (varName.compare("typeItem") == 0){
        this->typeItem = varValue;
    } else if (varName.compare("port") == 0){
        this->port = varValue;
    } else if (varName.compare("X11Forwarding") == 0){
        this->X11Forwarding = varValue;
    } else if (varName.compare("avecTunnel") == 0){
        this->avecTunnel = varValue;
    } else if (varName.compare("tunnelPort") == 0){
        this->tunnelPort = varValue;
    } else if (varName.compare("tunnelLocalPort") == 0){
        this->tunnelLocalPort = varValue;
    } else {
        QString message = tr("erreur de syntaxe dans le fichier de connexion") + tr("nom de variable inconnu : ") + varName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "erreur dans le fichier de connexion";
        qDebug() << "nom de variable inconnu : " << varName;
    }
}

//--------------------------------------------
//
//      Connexion::setVar
//
//--------------------------------------------
void Connexion::setVar(QString varName, QString varValue){
    if (varName.compare("idConnexion") == 0){
        this->idConnexion = varValue.toInt();
    } else if (varName.compare("level") == 0){
        this->level = varValue.toInt();
    } else if (varName.compare("commentaire") == 0){
        this->commentaire = varValue;
    } else if (varName.compare("typeItem") == 0){
        this->typeItem = varValue.toInt();
    } else if (varName.compare("groupeConnexionName") == 0){
        this->groupeConnexionName = varValue;
    } else if (varName.compare("label") == 0){
        this->label = varValue;
    } else if (varName.compare("nom") == 0){
        this->nom = varValue;
    } else if (varName.compare("adresseIP") == 0){
        this->adresseIP = varValue;
    } else if (varName.compare("port") == 0){
        this->port = varValue.toInt();
    } else if (varName.compare("X11Forwarding") == 0){
        if (varValue.compare("true") == 0){
            this->X11Forwarding = true;
        } else {
            this->X11Forwarding = false;
        }
    } else if (varName.compare("login") == 0){
        this->login = varValue;
    } else if (varName.compare("passwd") == 0){
        this->passwd = varValue;
    } else if (varName.compare("commande") == 0){
        this->commande = varValue;
    } else if (varName.compare("avecTunnel") == 0){
        this->avecTunnel = varValue.toInt();
    } else if (varName.compare("tunnelIP") == 0){
        this->tunnelIP = varValue;
    } else if (varName.compare("tunnelPort") == 0){
        this->tunnelPort = varValue.toInt();
    } else if (varName.compare("tunnelLogin") == 0){
        this->tunnelLogin = varValue;
    } else if (varName.compare("tunnelPassword") == 0){
        this->tunnelPassword = varValue;
    } else if (varName.compare("tunnelLocalPort") == 0){
        this->tunnelLocalPort = varValue.toInt();
    } else {
        QString message = tr("erreur de syntaxe dans le fichier de connexion") + tr("nom de variable inconnu : ") + varName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "erreur dans le fichier de connexion";
        qDebug() << "nom de variable inconnu : " << varName;
    }
}

//--------------------------------------------
//
//      Connexion::getQStringVar
//
//--------------------------------------------
QString Connexion::getQStringVar(QString varName){
    if (varName.compare("commentaire") == 0){
        return this->commentaire;
    } else if (varName.compare("groupeConnexionName") == 0){
        return this->groupeConnexionName;
    } else if (varName.compare("label") == 0){
         return label;
    } else if (varName.compare("nom") == 0){
        return this->nom;
    } else if (varName.compare("adresseIP") == 0){
        return this->adresseIP;
    } else if (varName.compare("login") == 0){
        return this->login;
    } else if (varName.compare("passwd") == 0){
        return this->passwd;
    } else if (varName.compare("commande") == 0){
        return this->commande;
    } else if (varName.compare("tunnelIP") == 0){
        return this->tunnelIP;
    } else if (varName.compare("tunnelLogin") == 0){
        return this->tunnelLogin;
    } else if (varName.compare("tunnelPassword") == 0){
        return this->tunnelPassword;
    } else {
        QString message = tr("Nom de variable inconnu : ") + varName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "erreur dans le fichier de connexion";
        qDebug() << "nom de variable inconnu : " << varName;
    }
    return nullptr;
}

//--------------------------------------------
//
//      Connexion::getIntVar
//
//--------------------------------------------
int Connexion::getIntVar(QString varName){
    if (varName.compare("idConnexion") == 0){
        return this->idConnexion;
    } else if (varName.compare("level") == 0){
        return this->level;
    } else if (varName.compare("typeItem") == 0){
        return this->typeItem;
    } else if (varName.compare("port") == 0){
        return this->port;
    } else if (varName.compare("X11Forwarding") == 0){
        return this->X11Forwarding;
    } else if (varName.compare("avecTunnel") == 0){
        return this->avecTunnel;
    } else if (varName.compare("tunnelPort") == 0){
        return this->tunnelPort;
    } else if (varName.compare("tunnelLocalPort") == 0){
        return this->tunnelLocalPort;
    } else {
        QString message = tr("Nom de variable inconnu : ") + varName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "erreur dans le fichier de connexion";
        qDebug() << "nom de variable inconnu : " << varName;
    }
    return -1;
}

//--------------------------------------------
//
//      Connexion::editConnexion
//
//--------------------------------------------
void Connexion::editConnexion(int mode){

    //Connexion connexionToEdit = items[0];
    editWidget = new QWidget();
    if ((mode == MODE_EDIT_CONNEXION) || (mode == MODE_EDIT_GROUPE)){
        editWidget->setWindowTitle("Edition d'une connexion");
    } else {
        editWidget->setWindowTitle("Création d'une connexion");
    }
    //QVBoxLayout *connexionBox = new QVBoxLayout();
    const char *message = "edition des parametres de la connexion";

    QLabel *idConnexion = new QLabel();
    idConnexion->setText(QString::number(this->idConnexion));

    QLabel *itemType = new QLabel();
    itemType->setText(QString::number(this->typeItem));

    editGroupeConnexionName = new QLineEdit();
    editGroupeConnexionName->setText(this->groupeConnexionName);

    QLabel *label = new QLabel();
    label->setText(this->getQStringVar("label")) ;

    editNom = new QLineEdit();
    editNom->setText(this->getQStringVar("nom"));

    editAdresseIP = new QLineEdit();
    editAdresseIP->setText(this->adresseIP);

    editPort = new QLineEdit();
    editPort->setText(QString::number(this->port));

    editX11Forwarding = new QCheckBox();
    if (this->X11Forwarding){
        editX11Forwarding->setChecked(true);
    } else {
        editX11Forwarding->setChecked(false);
    }

    editLogin = new QLineEdit();
    editLogin->setText(this->login);

    editPasswd = new QLineEdit();
    editPasswd->setText(this->passwd);

    editCommande = new QLineEdit();
    editCommande->setText(this->commande);

    editAvecTunnel = new QCheckBox();
    connect(editAvecTunnel, SIGNAL(clicked()), this, SLOT(refeshEditWidget()));
    if (this->avecTunnel){
        editAvecTunnel->setChecked(true);
    } else {
        editAvecTunnel->setChecked(false);
    }

    editTunnelIP = new QLineEdit();
    editTunnelIP->setText(this->tunnelIP);

    editTunnelPort = new QLineEdit();
    editTunnelPort->setText(QString::number(this->tunnelPort));

    editTunnelLogin = new QLineEdit();
    editTunnelLogin->setText(this->tunnelLogin);

    editTunnelPassword = new QLineEdit();
    editTunnelPassword->setText(this->tunnelPassword);

    editTunnelLocalPort = new QLineEdit();
    editTunnelLocalPort->setText(QString::number(this->tunnelLocalPort));

    editCommentaire = new QLineEdit();
    editCommentaire->setText(this->getQStringVar("commentaire"));

    //QGroupBox *formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr(message)));
    layout->addRow(new QLabel(tr("Id de connexion        :")), idConnexion);
    layout->addRow(new QLabel(tr("Type d'item            :")), itemType);
    layout->addRow(new QLabel(tr("Label de la connexion  :")), label);
    layout->addRow(new QLabel(tr("Nom du serveur         :")), editNom);
    layout->addRow(new QLabel(tr("Adresse IP             :")), editAdresseIP);
    layout->addRow(new QLabel(tr("Port                   :")), editPort);
    layout->addRow(new QLabel(tr("X11 Forwarding         :")), editX11Forwarding);
    layout->addRow(new QLabel(tr("login                  :")), editLogin);
    //layout->addRow(new QLabel(tr("password               :")), editPasswd);
    layout->addRow(new QLabel(tr("commande               :")), editCommande);
    layout->addRow(new QLabel(tr("tunneling              :")), editAvecTunnel);
    if (this->getIntVar("avecTunnel") == 1){
        layout->addRow(new QLabel(tr("IP rebond              :")), editTunnelIP);
        layout->addRow(new QLabel(tr("port rebond            :")), editTunnelPort);
        layout->addRow(new QLabel(tr("login rebond           :")), editTunnelLogin);
        //layout->addRow(new QLabel(tr("password rebond        :")), editTunnelPassword);
        layout->addRow(new QLabel(tr("local IP               :")), editTunnelLocalPort);
    }
    layout->addRow(new QLabel(tr("commentaire                :")), editCommentaire);

    QHBoxLayout *layoutBouttons = new QHBoxLayout;
    QPushButton *boutonEditSauver;
    if ((mode == MODE_EDIT_CONNEXION) || (mode == MODE_EDIT_GROUPE)){
        boutonEditSauver = new QPushButton("Sauver", editWidget);
    } else {
        boutonEditSauver = new QPushButton("Créer");
    }
    layoutBouttons->addWidget(boutonEditSauver);
    connect(boutonEditSauver, SIGNAL(clicked()), this, SLOT(saveEditedValues()));
    QPushButton *boutonEditAbandon = new QPushButton("Abandon");
    layoutBouttons->addWidget(boutonEditAbandon);
    connect(boutonEditAbandon, SIGNAL(clicked()), this, SLOT(abandonEdit()));
    layout->addRow(layoutBouttons);

    editWidget->setLayout(layout);
    editWidget->show();
}

//--------------------------------------------
//
//      Connexion::saveEditedValues
//
//--------------------------------------------
void Connexion::saveEditedValues(){
    qDebug() << "Connexion::saveEditedValues : debut";

    this->adresseIP = editAdresseIP->text();
    this->port = editPort->text().toInt();
    this->X11Forwarding=editX11Forwarding->isChecked();
    this->login = editLogin->text();
    //connexionCourante->passwd = editPasswd->text();
    this->commande = editCommande->text();
    this->avecTunnel=editAvecTunnel->isChecked();
    this->tunnelIP=editTunnelIP->text();
    this->tunnelPort=editTunnelPort->text().toInt();
    this->tunnelLogin=editTunnelLogin->text();
    //connexionCourante->tunnelPassword=editTunnelPassword->text();
    this->tunnelLocalPort=editTunnelLocalPort->text().toInt();

    this->commentaire = editCommentaire->text();

    editWidget->close();
    qDebug() << "Connexion::saveEditedValues : fin";
}


//--------------------------------------------
//
//      Connexion::refeshEditWidget
//
//--------------------------------------------
void Connexion::refeshEditWidget(){
    qDebug() << "Connexion::refeshEditWidget : debut";
    avecTunnel = !avecTunnel;
    editWidget->update();
    if (avecTunnel){
        qDebug() << "Connexion::refeshEditWidget => avecTunnel = true";
    } else {
        qDebug() << "Connexion::refeshEditWidget => avecTunnel = false";
    }
    qDebug() << "Connexion::refeshEditWidget : fin";
}

//--------------------------------------------
//
//      Connexion::abandonEdit
//
//--------------------------------------------
void Connexion::abandonEdit(){
    qDebug() << "Connexion::abandon : debut";

    editWidget->close();
    qDebug() << "Connexion::abandon : fin";
}


//--------------------------------------------
//
//      Connexion::displayInfosConnexion
//
//--------------------------------------------
void Connexion::displayInfosConnexion(){
    char tmp [100];
    qDebug() <<          "+-------------------------+---------------------------------+";
    sprintf(tmp,         "| idConnexion             | %30d  |", this->idConnexion);
    qDebug() << tmp;
    sprintf(tmp,         "| level                   | %30d  |", this->level);
    qDebug() << tmp;
    sprintf(tmp,         "| typeItem                | %30d  |", this->typeItem);
    qDebug() << tmp;
    if (this->typeItem == TYPE_GROUPE_CONNEXION){
        sprintf(tmp,     "| groupeConnexionName     | %30s  |", this->groupeConnexionName.toStdString().c_str());
        qDebug() << tmp;
    } else {
        sprintf(tmp,     "| commentaire             | %30s  |", this->commentaire.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| label                   | %30s  |", this->label.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| nom                     | %30s  |", this->nom.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| adresseIP               | %30s  |", this->adresseIP.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| port                    | %30d  |", this->port);
        qDebug() << tmp;
        sprintf(tmp,     "| X11Forwarding           | %30d  |", this->X11Forwarding);
        qDebug() << tmp;
        sprintf(tmp,     "| login                   | %30s  |", this->login.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| passwd                  | %30s  |", this->passwd.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| commande                | %30s  |", this->commande.toStdString().c_str());
        qDebug() << tmp;
        sprintf(tmp,     "| avecTunnel              | %30d  |", this->avecTunnel);
        qDebug() << tmp;
        if (this->avecTunnel){
            sprintf(tmp, "| tunnelIP                | %30s  |", this->tunnelIP.toStdString().c_str());
            qDebug() << tmp;
            sprintf(tmp, "| tunnelPort              | %30d  |", this->tunnelPort);
            qDebug() << tmp;
            sprintf(tmp, "| tunnelLogin             | %30s  |", this->tunnelLogin.toStdString().c_str());
            qDebug() << tmp;
            sprintf(tmp, "| tunnelPassword          | %30s  |", this->tunnelPassword.toStdString().c_str());
            qDebug() << tmp;
            sprintf(tmp, "| tunnelLocalPort         | %30d  |", this->tunnelLocalPort);
            qDebug() << tmp;
        }
    }
    qDebug() <<          "+-------------------------+---------------------------------+";
}

//--------------------------------------------
//
//      Connexion::lanceConnexion
//
//--------------------------------------------
void Connexion::lanceConnexion(Config *multiTermConfig){
    QString cdeTerminal = multiTermConfig->getTerminalAppName();
    QString cdeSsh = "ssh ";
    char cde[300];

    qDebug() << "Connexion::lanceConnexion";
    qDebug() << "on lance la connexion ssh sur " << label;

    // test forward X11
    if (X11Forwarding){
        cdeSsh += multiTermConfig->getOptionX11Forwarding();
        cdeSsh += " ";
    }
    QString tmp;
    tmp += cdeTerminal;
    tmp += " ";
    tmp += cdeSsh;
    tmp += login;
    tmp += "@";
    tmp += adresseIP;
    tmp += " ";
    if (! commande.isEmpty()){
        tmp += commande;
    } else {
        //tmp += cdeTerminal;
        //tmp += " -e ";
    }
    tmp += "&";

    qDebug() << "Connexion::lanceConnexion => execution de la commande " << tmp;
    sprintf(cde, "%s", tmp.toStdString().c_str());
    system(cde);

}

