
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTreeView>
#include <QtWidgets>

#include <string.h>

#include "multiterm.h"
#include "config.h"
#include "connexion.h"


//--------------------------------------------
//
//      MultiTerm::MultiTerm
//
//--------------------------------------------
//MultiTerm::MultiTerm(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MultiTerm)
MultiTerm::MultiTerm() {
    //qDebug() << "MultiTerm::MultiTerm => constructeur debut";


    // lecture du fichier de configuration
    //char configFilename[25] = "multiterm.cfg";
    QString configFilename = "multiTerm.cfg";
    QString homeDir = "~";
    multiTermConfig = new Config(homeDir,configFilename);

    for (int i = 0 ; i < 200 ; i++){
        listeConnexions[i] = nullptr;
    }

    createActions();
    createMenus();
    createArbreCnx();
    createTabCnx();

    QHBoxLayout *layoutPrincipal = new QHBoxLayout;

    QHBoxLayout *layoutArbreConnexion = new QHBoxLayout;
    layoutPrincipal->addLayout(layoutArbreConnexion);


    //qDebug() << "MultiTerm::MultiTerm => layout cree";
    layoutPrincipal->setMenuBar(menuBar);
    //qDebug() << "MultiTerm::MultiTerm => menuBar ajoute";
    layoutPrincipal->addWidget(arbreDesConnexions);
    //qDebug() << "MultiTerm::MultiTerm => arbreDesConnexions ajoute";
    //layoutPrincipal->addWidget(editTab);
    //qDebug() << "MultiTerm::MultiTerm => tabConnexions ajoute";
    setLayout(layoutPrincipal);
    //qDebug() << "MultiTerm::MultiTerm => display layout";

    //qDebug() << "MultiTerm::MultiTerm => constructeur fin";
}

//--------------------------------------------
//
//      MultiTerm::updateTitle
//
//--------------------------------------------
void MultiTerm::updateTitle(QString filename){
    //qDebug() << "MultiTerm::updateTitle => debut";
    QString tmp = appName;
    QStringList pathList = filename.split('/');
    QString fileNameWithoutPath = pathList[pathList.length()-1];

    if (!fileNameWithoutPath.isEmpty()){
        tmp += " (" + fileNameWithoutPath + ")";
    }
    //qDebug() << "MultiTerm::updateTitle => title = " << tmp;
    setWindowTitle(tmp);
    //qDebug() << "MultiTerm::updateTitle => fin";
}



//--------------------------------------------
//
//      MultiTerm::createArbreCnx
//
//--------------------------------------------
void MultiTerm::createArbreCnx(){
    //qDebug() << "MultiTerm::createArbreCnx => constructeur debut";

    arbreCnxGroupBox = new QGroupBox(tr("liste des connexions"));

    arbreDesConnexions = new QTreeWidget;
    arbreDesConnexions->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(arbreDesConnexions, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(doubleClicSurConnexion()));
    //arbreDesConnexions->itemDoubleClicked()
    connect(arbreDesConnexions,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextuelMenu(QPoint)));
    //QString homeDir = "/Users/obfe6300/devBruno/multiTerm/";
    //QString homeDir = multiTermConfig->getHomeDir();
    //connexionFilename = homeDir + "srvweb.cnx";
    //connexionFilename = homeDir + "srvweb.cnx";
    //QString fileName = homeDir + "multiTerm.cnx";
    //openListeConnexions(QString("srvweb.cnx"));
    openListeConnexions(connexionFilename);

    //layout->addWidget(arbreDesConnexions);

    //arbreCnxGroupBox->setLayout(layout);

    //qDebug() << "MultiTerm::createArbreCnx => constructeur fin";
}

//--------------------------------------------
//
//      MultiTerm::createTabCnx
//
//--------------------------------------------
void MultiTerm::createTabCnx(){
    //qDebug() << "MultiTerm::createTabCnx => constructeur debut";

    tabCnxGroupBox = new QGroupBox(tr("onglets de connexions"));
    tabCnxGroupBox->setTitle("liste des connexions");

    //qDebug() << "MultiTerm::createTabCnx => constructeur fin";
}

//--------------------------------------------
//
//      MultiTerm::createActions
//
//--------------------------------------------
void MultiTerm::createActions()
{
    //qDebug() << "MultiTerm::createActions => debut";

    actionQuitter = new QAction(tr("&Quitter"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionQuitter->setStatusTip(tr("Nouvelle Partie"));
    connect(actionQuitter,SIGNAL(triggered()), this, SLOT(quitter()));
    //connect(actionQuitter_MultiTerm, &QAction::triggered, this, &MultiTerm::quitter);
    //qDebug() << "MultiTerm::createActions => actionQuitter OK";

    actionOuvrir = new QAction(tr("&Ouvrir"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionOuvrir->setStatusTip(tr("Ouvrir une connexion"));
    connect(actionOuvrir,SIGNAL(triggered()), this, SLOT(openConnexion()));
    //qDebug() << "MultiTerm::createActions => actionOuvrir OK";

    actionSauvegarder = new QAction(tr("&Sauvegarder"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionSauvegarder->setStatusTip(tr("Sauvegarder une partie"));
    connect(actionSauvegarder,SIGNAL(triggered()), this, SLOT(sauvegarderConnexion()));
    //qDebug() << "MultiTerm::createActions => actionSauvegarder OK";

    actionSauvegarderSous = new QAction(tr("&Sauvegarder Sous"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionSauvegarderSous->setStatusTip(tr("Sauvegarder une partie sous un autre nom"));
    connect(actionSauvegarderSous,SIGNAL(triggered()), this, SLOT(sauvegarderSousConnexion()));
    //qDebug() << "MultiTerm::createActions => sauvegarderSousConnexion OK";

    actionAPropos = new QAction(tr("&A Propos"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionAPropos->setStatusTip(tr("A propos"));
    connect(actionAPropos,SIGNAL(triggered()), this, SLOT(aPropos()));
    //qDebug() << "MultiTerm::createActions => actionAPropos OK";

    actionNewGroupe = new QAction(tr("&Nouveau Groupe"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionNewGroupe->setStatusTip(tr("Nouvelle"));
    connect(actionNewGroupe,SIGNAL(triggered()), this, SLOT(newGroupe()));
    //qDebug() << "MultiTerm::createActions => NouveauGroupe OK";

    actionEditConnexion = new QAction(tr("&Edit Connexion"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionEditConnexion->setStatusTip(tr("Editer"));
    connect(actionEditConnexion,SIGNAL(triggered()), this, SLOT(editConnexion()));
    //qDebug() << "MultiTerm::createActions => editConnexion OK";

    actionNewConnexion = new QAction(tr("&Nouvelle Connexion"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionNewConnexion->setStatusTip(tr("Nouvelle"));
    connect(actionNewConnexion,SIGNAL(triggered()), this, SLOT(newConnexion()));
    //qDebug() << "MultiTerm::createActions => nouvelleConnexion OK";

    actionDeleteConnexion = new QAction(tr("&Supprimer Connexion"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionDeleteConnexion->setStatusTip(tr("Supprimer"));
    connect(actionDeleteConnexion,SIGNAL(triggered()), this, SLOT(deleteConnexion()));
    //qDebug() << "MultiTerm::createActions => deleteConnexion OK";

    actionLanceConnexion = new QAction(tr("&Lance Connexion"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionLanceConnexion->setStatusTip(tr("Ouvrir"));
    connect(actionLanceConnexion,SIGNAL(triggered()), this, SLOT(lanceConnexion()));
    //qDebug() << "MultiTerm::createActions => lanceConnexion OK";

    actionEchangeCleSsh = new QAction(tr("&Echange cl??s SSH"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionEchangeCleSsh->setStatusTip(tr("Echange cl??s SSH"));
    connect(actionEchangeCleSsh,SIGNAL(triggered()), this, SLOT(echangeCleSsh()));
    //qDebug() << "MultiTerm::createActions => lanceConnexion OK";

    actionEditConfiguration = new QAction(tr("&Edit Configuration"), this);
    //actionA_propos->setShortcuts(QKeySequence::New);
    actionEditConfiguration->setStatusTip(tr("Edit Config"));
    connect(actionEditConfiguration,SIGNAL(triggered()), this, SLOT(editConfiguration()));
    //qDebug() << "MultiTerm::createActions => editConfiguration OK";

    actionListeConnexions = new QAction(tr("&display liste connexions"), this);
    actionListeConnexions->setStatusTip(tr("liste connexion"));
    connect(actionListeConnexions,SIGNAL(triggered()), this, SLOT(displayListeConnexions()));

    actionRedrawArbre = new QAction(tr("&redraw arbre"), this);
    actionRedrawArbre->setStatusTip(tr("redessine l'arbre"));
    connect(actionRedrawArbre,SIGNAL(triggered()), this, SLOT(redrawArbre()));

    //qDebug() << "MultiTerm::createActions => fin";
}

//--------------------------------------------
//
//      MultiTerm::createMenus
//
//--------------------------------------------
void MultiTerm::createMenus()
{
    //qDebug() << "MultiTerm::createMenus => debut";
    menuBar = new QMenuBar;

    //menuFichier->addSeparator();
    //qDebug() << "MultiTerm::createMenus => addSeparator OK";

    menuFichier = menuBar->addMenu(tr("&Fichier"));
    //qDebug() << "MultiTerm::createMenus => menuFichier OK";
    menuFichier->addAction(actionOuvrir);
    //qDebug() << "MultiTerm::createMenus => menuFichier addAction actionOuvrir OK";
    menuFichier->addAction(actionSauvegarder);
    //qDebug() << "MultiTerm::createMenus => menuFichier addAction actionSauvegarder OK";
    menuFichier->addAction(actionSauvegarderSous);
    //qDebug() << "MultiTerm::createMenus => menuFichier addAction actionSauvegarderSous OK";
    menuFichier->addAction(actionQuitter);
    //qDebug() << "MultiTerm::createMenus => menuFichier addAction actionQuitter OK";
    //qDebug() << "MultiTerm::createMenus => menuFichier OK";

    menuAide = menuBar->addMenu(tr("&Aide"));
    //qDebug() << "MultiTerm::createMenus => Aide OK";
    menuAide->addAction(actionAPropos);
    menuAide->addAction(actionEditConfiguration);
    menuAide->addAction(actionListeConnexions);
    menuAide->addAction(actionRedrawArbre);
    //qDebug() << "MultiTerm::createMenus => menuAide addAction actionAPropos OK";
    //qDebug() << "MultiTerm::createMenus => menuAide OK";

    //qDebug() << "MultiTerm::createMenus => fin";
}

//--------------------------------------------
//
//      MultiTerm::contextuelMenu
//
//--------------------------------------------
void MultiTerm::contextuelMenu(QPoint point) {
//void MultiTerm::contextuelMenu() {
    //qDebug() << "MultiTerm::contextuelMenu => debut";

    QMenu menu(this);
    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    //int idxConnexion = arbreDesConnexions->indexOfTopLevelItem(items[0]);
    //int idxConnexion = arbreDesConnexions->columnCount();
    //qDebug() << "MultiTerm::contextuelMenu => clic sur l'item N?? " << idxConnexion;
    QString labelConnexion = items[0]->text(0);
    //QModelIndex idConnexion = arbreDesConnexions->indexFromItem(items[0],0);
    //qDebug() << "MultiTerm::contextuelMenu => label cliqu?? " << labelConnexion;
    //qDebug() << "MultiTerm::contextuelMenu => clic en position " << idConnexion;
    //connexionCourante = &listeConnexions[idConnexion];
    menu.addAction(actionEditConnexion);
    menu.addAction(actionNewConnexion);
    menu.addAction(actionDeleteConnexion);
    menu.addAction(actionLanceConnexion);
    menu.addAction(actionEchangeCleSsh);
    menu.addSeparator();
    menu.addAction(actionNewGroupe);
    QWidget *win = QApplication::activeWindow();
    QPoint pos = point;
    pos += win->pos();
    menu.exec(pos);
    //qDebug() << "MultiTerm::contextuelMenu => fin";
}

//--------------------------------------------
//
//      MultiTerm::doubleClicSurConnexion
//
//--------------------------------------------
void MultiTerm::doubleClicSurConnexion(){
    qDebug() << "MultiTerm::doubleClicSurConnexion => debut";
    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    QString itemText = items[0]->text(0);


    int index;
    for (index = 0 ; index < 200 ; index++){
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            QString tmpLabel = connexionCourante->getQStringVar("label");
            qDebug() << "connexion " << tmpLabel;
            if (tmpLabel == itemText) {
                qDebug() << "MultiTerm::doubleClicSurConnexion => on a trouve la connexion sur laquelle on a double clique : " << index;
                break;
            }
        } else {
            return;     // on a pas trouve la connexion correspondante
        }
    }

    connexionCourante->lanceConnexion(multiTermConfig);

    qDebug() << "MultiTerm::doubleClicSurConnexion => fin";
}

//--------------------------------------------
//
//      MultiTerm::aPropos
//
//--------------------------------------------
void MultiTerm::aPropos(){
    qDebug() << "MultiTerm::aPropos => debut";

    QString message;
    QMessageBox messageBox = QMessageBox(this);
    messageBox.setStandardButtons(QMessageBox::Ok);
    message += "MultiTerm\n\n";
    message += this->description + " \n\n";
    message += this->version + " \n";
    message += this->auteur + " \n\n";
    message += this->anneeVersion + " \n";
    messageBox.setInformativeText(message);

    messageBox.setWindowTitle("Quitter");

    messageBox.exec();

    qDebug() << "MultiTerm::aPropos => fin";
}

//--------------------------------------------
//
//      MultiTerm::editConfiguration
//
//--------------------------------------------
void MultiTerm::editConfiguration(){
    qDebug() << "MultiTerm::editConfiguration => debut";

    multiTermConfig->editConfig();

    qDebug() << "MultiTerm::editConfiguration => fin";
}

//--------------------------------------------
//
//      MultiTerm::closeEvent
//
//--------------------------------------------
void MultiTerm::closeEvent(QCloseEvent *event){
    quitter();
    event->ignore();
}

//--------------------------------------------
//
//      MultiTerm::quitter
//
//--------------------------------------------
void MultiTerm::quitter()
{
    qDebug() << "MultiTerm::quitter";

    QString message;
    QMessageBox messageBox = QMessageBox(this);
    if (dataConnexionModifee){
        message = "Attention les donn??es de connexion n'ont pas ??t?? sauvegard??es \n";
        messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::Save);
    } else {
        messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    }
    message += "Voulez vous vraiment quitter l'application ? ";
    messageBox.setInformativeText(message);

    messageBox.setWindowTitle("Quitter");

    int status = messageBox.exec();

    switch(status){
    case QMessageBox::Ok:
        _Exit(0);
        break;
    case QMessageBox::Save:
        sauvegarderConnexion();
        break;
    }
}

//--------------------------------------------
//
//      MultiTerm::echangeCleSsh()
//
//--------------------------------------------
void MultiTerm::echangeCleSsh(){
    qDebug() << "MultiTerm::echangeCleSsh => debut";

    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    QString itemText = items[0]->text(0);
    qDebug() << "MultiTerm::echangeCleSsh => itemText = " << itemText;

    int index;
    for (index = 0 ; index < 200 ; index++){
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            QString tmpLabel = connexionCourante->getQStringVar("label");
            qDebug() << "connexion " << tmpLabel;
            if (tmpLabel == itemText) {
                qDebug() << "MultiTerm::echangeCleSsh => on a trouve la connexion avec laquelle faire l'echange de cle ssh : " << index;
                break;
            }
        } else {
            return;     // on a pas trouve la connexion correspondante
        }
    }

    QString cdeTerminal = multiTermConfig->getTerminalAppName();
    //cat .ssh/id_rsa.pub | ssh ubuntu@192.168.56.101 'cat >> .ssh/authorized_keys'
    char cde[300];
    QString tmp;
    tmp += cdeTerminal;
    tmp += " \"cat ~/.ssh/id_rsa.pub | ssh ";;
    tmp += connexionCourante->getQStringVar("login");
    tmp += "@";
    tmp += connexionCourante->getQStringVar("passwd");
    tmp += " 'cat >> .ssh/authorized_keys' \"";
    qDebug() << "MultiTerm::echangeCleSsh => execution de la commande " << tmp;
    sprintf(cde, "%s", tmp.toStdString().c_str());
    //system(cde);
    qDebug() << "MultiTerm::echangeCleSsh => fin";
}


//--------------------------------------------
//
//      MultiTerm::openConnexion()
//
//--------------------------------------------
void MultiTerm::openConnexion(){
    qDebug() << "MultiTerm::openConnexion => debut";

    //QString directory = "/Users/obfe6300/devBruno/multiTerm/";
    QString directory = multiTermConfig->getHomeDir();
    qDebug() << "recherche dans le repertoire " << directory;
    connexionFilename = QFileDialog::getOpenFileName(this, tr("Ouvrir connexion"), directory, tr("Connexions (*.cnx)"));
    if (!connexionFilename.isEmpty()){
        qDebug() << "Ouverture du fichier decrivant les connexions : " << connexionFilename;
        openListeConnexions(connexionFilename);
    } else {
        qDebug() << "abandon d'ouverture de connexion";
        connexionFilename = multiTermConfig->getCnxFileName();
        return;
    }
    qDebug() << "MultiTerm::openConnexion => fin";
}

//--------------------------------------------
//
//      MultiTerm::creeConnexion()
//
//--------------------------------------------
void MultiTerm::creeConnexion(){
    connexionCourante = new Connexion();
}


//--------------------------------------------
//
//      MultiTerm::openListeConnexion()
//
//--------------------------------------------
void MultiTerm::openListeConnexions(QString fileName){

    QTreeWidgetItem *itemGroupeConnexion;
    QTreeWidgetItem *itemConnexion;
    indexNewConnexion= 0;
    arbreDesConnexions->clear();

    //qDebug() << "MultiTerm::openListeConnexion => debut";

    if (fileName.isEmpty()){
        fileName = multiTermConfig->getHomeDir();
        fileName += "/";
        fileName += multiTermConfig->getCnxFileName();
    }

    QFile fileCnx = QFile(fileName);
    if (!fileCnx.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString message = tr("impossible d'ouvrir le fichier de connexions ") + fileName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "impossible d'ouvrir le fichier de connexions " << fileName;
        return;
    }

    updateTitle(fileName);
    connexionFilename = fileName;

    //qDebug() << "MultiTerm::openListeConnexions => traitement des donnnees du fichier " << fileName;
    // niveauArbre values entres {}
    // incremente a chaque {
    // decremente a chaque }
    int niveauArbre = 0;
    // typeData  => type de donnees attendue a ce niveau
    // 1 : definition groupe de connexions
    // 2 : definition de connexion
    int typeData = 0;
    int idItem = 0;
    QString groupeConnexionName;
    QTreeWidgetItem *itemParent[10];
    while (!fileCnx.atEnd()) {
        int index;
        QByteArray line = fileCnx.readLine();
        QString qLine = QString(line).simplified();
        //qDebug() << "--------------------------------------------";
        //qDebug() << "ligne a analyser : " << qLine;

        // test si ligne contient un commentaire
        index = qLine.indexOf('#');
        if (index >= 0){
            // on supprime ce qu'il y a apres le #
            qLine = qLine.left(index);
        }

        // test ouverture {
        index = qLine.indexOf('{');
        if (index >= 0) {
            niveauArbre++;
            idItem++;
            // on supprime ce qu'il y a jusqu'a l'{
            qLine = qLine.right(qLine.length() - index - 1);
            if (typeData == 0) typeData=1;
            //qDebug() << " { => " << niveauArbre << " ; " << typeData;
         }

        // test fermeture }
        index = qLine.indexOf('}');
        if (index >= 0) {
            niveauArbre--;
            typeData=1;
            // on supprime ce qu'il y a apres l'{
            qLine = qLine.left(index);
            //qDebug() << " } => " << niveauArbre << " ; " << typeData;
        }

        // test ligne vide
        if (qLine.trimmed().length() == 0){
            continue;
        }

        // analyse d'une variable = valeur
        index = qLine.indexOf('=');
        QString varName = qLine.left(index).trimmed();
        QString varValue = qLine.right(qLine.size() - index - 1).trimmed();
        //qDebug() << "traitement de <" << varName << ">=<" << varValue << ">";
        switch (typeData){
        case 0: // pas d'initialisation de variables possible dans ce mode
            break;
        case 1 : // variables de niveau groupe de connexions
            if (varName.compare("groupeConnexion") == 0){
                //qDebug() << "variable de niveau groupe de connexion " << varName << "=" << varValue;
                // creation du groupe de cnnexion dans l'arbre des connexions
                itemGroupeConnexion = new QTreeWidgetItem();
                itemGroupeConnexion->setText(0,varValue);

                if (niveauArbre == 1){
                    //qDebug() << "creation d'un fils au niveau racine";
                    arbreDesConnexions->addTopLevelItem(itemGroupeConnexion);
                    itemParent[niveauArbre] = itemGroupeConnexion;
                } else {
                    //qDebug() << "creation d'un fils au niveau " << (niveauArbre - 1);
                    itemParent[niveauArbre - 1]->addChild(itemGroupeConnexion);
                    itemParent[niveauArbre] = itemGroupeConnexion;
                }
                //qDebug() << "creation d'un groupe de connexion " << varValue;
                creeConnexion();
                listeConnexions[indexNewConnexion] = connexionCourante;
                //connexionCourante->setIdConnexion(indexNewConnexion);
                connexionCourante->setVar("idConnexion", QString::number(indexNewConnexion));
                indexNewConnexion++;
                listeConnexions[indexNewConnexion] = nullptr;       // on reset la connexion suivante
                connexionCourante->setVar("level", niveauArbre);
                connexionCourante->setVar("typeItem", TYPE_GROUPE_CONNEXION);
                connexionCourante->setVar("groupeConnexionName", varValue);
                QString tmp = QString::number(indexNewConnexion-1);
                tmp += "->";
                tmp += varValue;
                connexionCourante->setVar("label", tmp);
                typeData=1;
                break;
            } else if (varName.compare("connexion") == 0){
                //qDebug() << "on commence une connexion " << varName << "=" << varValue;
                itemConnexion = new QTreeWidgetItem;
                creeConnexion();
                //qDebug() << "ajout de la connexion " << indexNewConnexion;
                listeConnexions[indexNewConnexion] = connexionCourante;
                connexionCourante->setVar("idConnexion", indexNewConnexion);
                connexionCourante->setVar("groupeConnexionName", listeConnexions[indexNewConnexion-1]->getQStringVar("groupeConnexionName"));
                indexNewConnexion++;
                listeConnexions[indexNewConnexion] = nullptr;       // on reset la connexion suivante     // on reset la connexion suivante
                connexionCourante->setVar("level", niveauArbre);
                connexionCourante->setVar("typeItem", TYPE_CONNEXION);
                connexionCourante->setVar("port", 0);
                QString tmp = QString::number(indexNewConnexion-1);
                tmp += "->";
                tmp += varValue;
                connexionCourante->setVar("label", tmp);
                itemConnexion->setText(0,tmp);
                itemGroupeConnexion->addChild(itemConnexion);
                typeData=2;
            } else {
                QString message = tr("erreur de syntaxe dans le fichier de connexion") + tr("nom de variable inconnu : ") + varName;
                QMessageBox::information(NULL,tr("ERREUR"), message);
                qDebug() << "erreur dans le fichier de connexion";
                qDebug() << "nom de variable inconnu : " << varName;
            }
            break;
        case 2 : // variable de niveau connexion
            //qDebug() << "donnee de connexion " << varName << "=" << varValue;
            if (varName.compare("connexion") == 0){
                //qDebug() << "on commence une connexion " << varName << "=" << varValue;
                connexionCourante->setVar("label", varValue);
                //connexionCourante->setVar(Label(varValue);
            } else {
                connexionCourante->setVar(varName, varValue);
            }
            break;
        default:
            QString message = tr("incoherence dans les { et }");
            QMessageBox::information(NULL,tr("ERREUR"), message);
            qDebug() << "ERREUR : incoherence dans les { et } => typeData = " << typeData;
        }

        //qDebug() << "niveauArbre = " << niveauArbre << " ; typeData = " << typeData ;

    }

    fileCnx.close();
    //qDebug() << "MultiTerm::openListeConnexion => affiche liste des connexions";
    //displayListeConnexions();

    //qDebug() << "MultiTerm::openListeConnexion => fin";

}

//--------------------------------------------
//
//      MultiTerm::sauvegarderConnexion
//
//--------------------------------------------
void MultiTerm::sauvegarderConnexion(){
    qDebug() << "MultiTerm::sauvegarderConnexion : debut";

    sauvegardeFichierConnexion(connexionFilename);

    qDebug() << "MultiTerm::sauvegarderConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::sauvegarderSousConnexion
//
//--------------------------------------------
void MultiTerm::sauvegarderSousConnexion(){
    qDebug() << "MultiTerm::sauvegarderSousPartie";

    QString directory = multiTermConfig->getHomeDir();
    connexionFilename = QFileDialog::getSaveFileName(this, tr("Sauvegarder fichier des connexions"), directory, tr("Connexions (*.cnx)"));
    if (!connexionFilename.isEmpty()){
        qDebug() << "Sauvegarde de la connexion : " << connexionFilename;
        sauvegardeFichierConnexion(connexionFilename);
        updateTitle(connexionFilename);
    } else {
        qDebug() << "abandon de la sauvegarde de connexion";
    }
}

//--------------------------------------------
//
//      MultiTerm::ecritLigne
//
//--------------------------------------------
void MultiTerm::ecritLigne(QString ligne, int nbTab){
    //qDebug() << "MultiTerm::ecritLigne -> " << ligne << " avec " << nbTab << " tabulations";
    QString tmp = "";
    while (--nbTab > 0){
        tmp += "\t";
    }
    tmp += ligne;
    tmp += "\n";
    fileCnx->write(tmp.toStdString().c_str());
    //qDebug() << "MultiTerm::ecritLigne -> " << tmp;
}

//--------------------------------------------
//
//      MultiTerm::sauvegardeFichierConnexion
//
//--------------------------------------------
void MultiTerm::sauvegardeFichierConnexion(QString fileName){
    qDebug() << "MultiTerm::sauvegardeFichierConnexion : debut -> " << fileName;

    fileCnx = new QFile(fileName);
    if (!fileCnx->open(QIODevice::WriteOnly | QIODevice::Text)){
        QString message = tr("impossible d'ouvrir le fichier de connexions ") + fileName;
        QMessageBox::information(NULL,tr("ERREUR"), message);
        qDebug() << "impossible d'ouvrir le fichier de connexions <" << fileName << ">";
        return;
    }

    // valeurs de level = niveau d'accolades
    int level = 0;
    QString ligne;
    // on traite une connexion existante
    int index = 0;
    connexionCourante = listeConnexions[index++];
    if (connexionCourante == nullptr){
        qDebug() << "ERREUR : liste des connexions vide";
        return;
    }
    QString oldGroupeConnexionName = connexionCourante->getQStringVar("groupeConnexionName");
    while (connexionCourante != nullptr){
        //connexionCourante->displayInfosConnexion();
        //return;
        //ligne = "";
        level = connexionCourante->getIntVar("level");
        if (connexionCourante->getIntVar("typeItem") == TYPE_GROUPE_CONNEXION){
            // on traite un groupe de connexions
            //qDebug() << "traitement d'un groupe de connexion";
            ecritLigne("{ groupeConnexion = " + connexionCourante->getQStringVar("groupeConnexionName"), level);
            oldGroupeConnexionName = connexionCourante->getQStringVar("groupeConnexionName");
            level++;
            qDebug() << "Sauvegarde du groupe de connexion " << index << " => " << connexionCourante->getQStringVar("groupeConnexionName");;
            connexionCourante = listeConnexions[index++];
            int newLevel = 1;
            if (connexionCourante != nullptr) {
                newLevel = connexionCourante->getIntVar("level");
            }
            while (--level >= newLevel){
                ecritLigne("}",level);
            }
        } else {
            // on traite une connexion
            //qDebug() << "traitement d'une connexion";
            QString tmpLabel;
            int idx = connexionCourante->getQStringVar("label").indexOf("->");
            tmpLabel = connexionCourante->getQStringVar("label").right(connexionCourante->getQStringVar("label").length() - idx - 2);
            ecritLigne("{ connexion = " + tmpLabel, level);
            level++;
            //ecritLigne("idConnexion = " + QString::number(connexionCourante->idConnexion), level);
            //ecritLigne("level = " + QString::number(connexionCourante->level), level);
            ecritLigne("commentaire = " + connexionCourante->getQStringVar("commentaire"), level);
            ecritLigne("nom = " + connexionCourante->getQStringVar("nom"), level);
            ecritLigne("adresseIP = " + connexionCourante->getQStringVar("adresseIP"),level);
            ecritLigne("port = " + QString::number(connexionCourante->getIntVar("port")),level);
            if (connexionCourante->getIntVar("X11Forwarding")){
                ecritLigne("X11Forwarding = true",level);
            } else {
                ecritLigne("X11Forwarding = false",level);
            }

            ecritLigne("login = " + connexionCourante->getQStringVar("login"),level);
            //ecritLigne("password = " + connexionCourante->passwd,level);
            if (!connexionCourante->getQStringVar("commande").isEmpty()){
                ecritLigne("commande = " + connexionCourante->getQStringVar("commande"),level);
            }
            //ecritLigne("tunnel = " + QString::number(connexionCourante->avecTunnel),level);
            if (connexionCourante->getIntVar("avecTunnel")){
                ecritLigne("IP rebond = " + connexionCourante->getQStringVar("tunnelIP"),level);
                ecritLigne("port rebond = " + QString::number(connexionCourante->getIntVar("tunnelPort")),level);
                ecritLigne("login rebond = " + connexionCourante->getQStringVar("tunnelLogin"),level);
                //ecritLigne("password rebond = " + connexionCourante->tunnelPassword,level);
                ecritLigne("port local = " + QString::number(connexionCourante->getIntVar("tunnelLocalPort")),level);
            }
            //level--;
            qDebug() << "Sauvegarde de la connexion " << index << " => " << connexionCourante->getQStringVar("nom");;
            connexionCourante = listeConnexions[index++];
            int newLevel = 1;
            if (connexionCourante != nullptr) {
                newLevel = connexionCourante->getIntVar("level");
            }
            while (--level >= newLevel){
                ecritLigne("}",level);
            }
        }
    }

    dataConnexionModifee = false;
    qDebug() << "fin d'ecriture du fichier";

    fileCnx->close();
    qDebug() << "MultiTerm::sauvegardeFichierConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::editItem
//
//--------------------------------------------
void MultiTerm::editItem(int mode){
    qDebug() << "MultiTerm::editItem => debut";
    switch (mode){
    case MODE_EDIT_CONNEXION:
        //qDebug() << "MultiTerm::editItem => edition d'une connexion";
        break;
    case MODE_EDIT_GROUPE:
        qDebug() << "MultiTerm::editItem => edition d'un groupe de connexion";
        qDebug() << "a develloper";
        return;
        break;
    case MODE_NEW_CONNEXION:
        qDebug() << "MultiTerm::editItem => creation d'une connexion";
        qDebug() << "a develloper";
        return;
        break;
    case MODE_NEW_GROUPE:
        qDebug() << "MultiTerm::editItem => creation d'un groupe de connexion";
        qDebug() << "a develloper";
        return;
        break;
    default:
        qDebug() << "mode non defini => on quitte la fonction d'edition";
        return;
    }

    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    QString itemText = items[0]->text(0);
    qDebug() << "MultiTerm::editItem => itemText = " << itemText;

    int index;
    for (index = 0 ; index < 200 ; index++){
        qDebug() << "MultiTerm::editItem => test connexion " << index;
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            QString tmpLabel = connexionCourante->getQStringVar("label");
            qDebug() << "MultiTerm::editItem => connexion " << tmpLabel;
            if (tmpLabel == itemText) {
                qDebug() << "MultiTerm::editItem => on a trouve la connexion a editer : " << index;
                break;
            }
        } else {
            qDebug() << "MultiTerm::editItem => listeConnexion[index] = nullptr => on quitte la fonction";
            return;     // on a pas trouve la connexion correspondante
        }
    }

    if (index >= 200){
        qDebug() << "MultiTerm::editItem => impossible de trouver cet item a editer";
        return;
    }

    connexionCourante->editConnexion(mode);


    qDebug() << "MultiTerm::editItem => fin";
}
//--------------------------------------------
//
//      MultiTerm::newGroupe
//
//--------------------------------------------
void MultiTerm::newGroupe(){
    qDebug() << "MultiTerm::newGroupe : debut";

    // todo preparer la creation du groupe
    editItem(MODE_NEW_GROUPE);

    qDebug() << "MultiTerm::newGroupe : fin";
}

//--------------------------------------------
//
//      MultiTerm::refreshTreeConnexion
//
//--------------------------------------------
void MultiTerm::refreshTreeConnexion(){
    //qDebug() << "MultiTerm::refreshTreeConnexion : debut";

    //qDebug() << "MultiTerm::refreshTreeConnexion => ";
    arbreDesConnexions->update();

    //qDebug() << "MultiTerm::refreshTreeConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::editConnexion
//
//--------------------------------------------
void MultiTerm::editConnexion(){
    //qDebug() << "MultiTerm::editConnexion : debut";

    editItem(MODE_EDIT_CONNEXION);


    //qDebug() << "MultiTerm::editConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::newConnexion
//
//--------------------------------------------
void MultiTerm::newConnexion(){
    qDebug() << "MultiTerm::newConnexion : debut";
    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    int idxArbreCnx = arbreDesConnexions->indexOfTopLevelItem(items[0]);
    QString itemText = items[0]->text(0);
    qDebug() << "MultiTerm::newConnexion => itemText = " << itemText;

    int index;
    for (index = 0 ; index < 200 ; index++){
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            if (connexionCourante->getIntVar("typeItem") == 0) {
                // on a clique sur un groupe de connexion
                if (connexionCourante->getQStringVar("groupeConnexionName") == itemText){
                    qDebug() << "MultiTerm::newConnexion => on a trouve la connexion a creer sur tete de groupe : " << index;
                    break;
                }
            } else {
                //qDebug() << "MultiTerm::newConnexion => connexion " << connexionCourante->getQStringVar("label");
                if (connexionCourante->getQStringVar("label") == itemText) {
                    qDebug() << "MultiTerm::newConnexion => on a trouve la connexion a creer apres une connexion : " << index;
                    break;
                }
            }
        } else {
            qDebug() << "MultiTerm::newConnexion => on n'a pas trouve la connexion a creer";
            return;     // on a pas trouve la connexion correspondante
        }
    }

    if (index >= 200){
        qDebug() << "MultiTerm::newConnexion => impossible de trouver cet item a editer";
        return;
    }

    creeConnexion();
    qDebug() << "MultiTerm::newConnexion => cr??ation d'une connexion a l'item " << indexNewConnexion;
    // insertion de la nouvelle connexion dans la liste des connexions
    for (int i = indexNewConnexion ; i == index ; i--){
        listeConnexions[i] = listeConnexions[i-1];
    }
    listeConnexions[indexNewConnexion]=connexionCourante;
    connexionCourante->setVar("idConnexion", indexNewConnexion);
    connexionCourante->setVar("level", listeConnexions[indexNewConnexion-1]->getIntVar("level"));
    connexionCourante->setVar("typeItem", TYPE_CONNEXION);
    connexionCourante->setVar("port", 22);
    modeEdition = MODE_NEW_CONNEXION;
    listeConnexions[indexNewConnexion-1]->displayInfosConnexion();
    connexionCourante->displayInfosConnexion();
    connexionCourante->editConnexion(modeEdition);
    connexionCourante->setVar("groupeConnexionName",listeConnexions[indexNewConnexion-1]->getQStringVar("groupeConnexionName"));

    QTreeWidgetItem *itemConnexion;
    itemConnexion = new QTreeWidgetItem;

    QString tmp = QString::number(indexNewConnexion);
    tmp += "->";
    tmp += connexionCourante->getQStringVar("nom");
    qDebug() << "MultiTerm::newConnexion => nom de la nouvelle connnexion = " << connexionCourante->getQStringVar("nom");
    connexionCourante->setVar("label", tmp);
    qDebug() << "MultiTerm::newConnexion => label de la nouvelle connnexion = " << tmp;
    //itemConnexion->setText(0,varValue);
    itemConnexion->setText(0,tmp);
    arbreDesConnexions->insertTopLevelItem(idxArbreCnx,itemConnexion);
    arbreDesConnexions->repaint();
    indexNewConnexion++;

    qDebug() << "MultiTerm::newConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::deleteConnexion
//
//--------------------------------------------
void MultiTerm::deleteConnexion(){
    qDebug() << "MultiTerm::deleteConnexion : debut";

    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    //int idxArbreCnx = arbreDesConnexions->indexOfTopLevelItem(items[0]);
    QString itemText = items[0]->text(0);
    qDebug() << "MultiTerm::deleteConnexion => itemText = " << itemText;

    int index;
    for (index = 0 ; index < 200 ; index++){
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            if (connexionCourante->getIntVar("typeItem") == 0) {
                // on a clique sur un groupe de connexion
                if (connexionCourante->getQStringVar("groupeConnexionName") == itemText){
                    qDebug() << "MultiTerm::deleteConnexion => on a trouve le groupe ?? supprimer : " << index;
                    break;
                }
            } else {
                if (connexionCourante->getQStringVar("label") == itemText) {
                    qDebug() << "MultiTerm::deleteConnexion => on a trouve la connexion a supprimer : " << index;
                    break;
                }
            }
        } else {
            qDebug() << "MultiTerm::deleteConnexion => on n'a pas trouve la connexion a supprimer";
            return;     // on a pas trouve la connexion correspondante
        }
    }

    qDebug() << "suppression de l'item : " << index;

    int idx = index;
    while (listeConnexions[idx + 1] != nullptr){
        listeConnexions[idx] = listeConnexions[idx + 1];
    }
    listeConnexions[idx] = nullptr;
    arbreDesConnexions->removeItemWidget(items[0],0);
    arbreDesConnexions->repaint();
    indexNewConnexion--;
    qDebug() << "MultiTerm::deleteConnexion : fin";
}

//--------------------------------------------
//
//      MultiTerm::lanceConnexion
//
//--------------------------------------------
void MultiTerm::lanceConnexion(){
    QList<QTreeWidgetItem*> items = arbreDesConnexions->selectedItems();
    QString itemText = items[0]->text(0);
    qDebug() << "MultiTerm::lanceConnexion => itemText = " << itemText;

    int index;
    for (index = 0 ; index < 200 ; index++){
        if (listeConnexions[index] != nullptr) {
            connexionCourante = listeConnexions[index];
            qDebug() << "connexion " << connexionCourante->getQStringVar("label");
            if (connexionCourante->getQStringVar("label") == itemText) {
                //qDebug() << "MultiTerm::lanceConnexion => on a trouve la connexion a lancer : " << index;
                break;
            }
        } else {
            return;     // on a pas trouve la connexion correspondante
        }
    }

    if (index >= 200){
        qDebug() << "MultiTerm::lanceConnexion => impossible de trouver cet item a editer";
        return;
    }

    connexionCourante->lanceConnexion(multiTermConfig);
}

//--------------------------------------------
//
//      MultiTerm::displayListeConnexions
//
//--------------------------------------------
void MultiTerm::displayListeConnexions(){
    for (int idx = 0 ; idx < indexNewConnexion ; idx ++){
        listeConnexions[idx]->displayInfosConnexion();
    }
}

//--------------------------------------------
//
//      MultiTerm::redrawArbre
//
//--------------------------------------------
void MultiTerm::redrawArbre(){
    qDebug() << "MultiTerm::redrawArbre : debut";
    //arbreDesConnexions->clear();
    arbreDesConnexions->repaint();
    arbreDesConnexions->update();
    qDebug() << "MultiTerm::redrawArbre : fin";
}
