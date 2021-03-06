#include "config.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>


//--------------------------------------------
//
//      Config::Config
//
//--------------------------------------------
Config::Config(QString homeDir, QString configFileName){
    this->homeDir = homeDir;
    this->configFileName = configFileName;

    cnxFileName = "multiTerm.cnx";
    terminalApp = "xterm";
    optionX11Forwarding = "";
    datasModified=false;
    analyseConfigFile();
}

//--------------------------------------------
//
//      Config::getHomeDir
//
//--------------------------------------------
QString Config::getHomeDir(){
    return homeDir;
}

//--------------------------------------------
//
//      Config::getOptionX11Forwarding
//
//--------------------------------------------
QString Config::getOptionX11Forwarding(){
    return optionX11Forwarding;
}

//--------------------------------------------
//
//      Config::getCnxFileName
//
//--------------------------------------------
QString Config::getCnxFileName(){
    return cnxFileName;
}

//--------------------------------------------
//
//      Config::getTerminalAppName
//
//--------------------------------------------
QString Config::getTerminalAppName(){
    return terminalApp;
}

//--------------------------------------------
//
//      Config::getShellLocal
//
//--------------------------------------------
QString Config::getShellLocal(){
    return shellLocal;
}

//--------------------------------------------
//
//      Config::analyseConfigFile
//
//--------------------------------------------
void Config::analyseConfigFile(){
    //qDebug() << "Config::analyseConfigFile : debut";

    QString tmFileName = configFileName;
    QFile file = QFile(tmFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString message = tr("impossible d'ouvrir le fichier de configuration ") + tmFileName;
        QMessageBox::information(NULL,"ERREUR", message);
        qDebug() << "impossible d'ouvrir le fichier de configuration " << tmFileName;
        return;
    }
    int indexLigne = 0;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString qLine = QString(line).simplified();
        //qDebug() << "analyse de la ligne " << indexLigne << " <" << qLine << ">";
        indexLigne++;
        // test si ligne contient un commentaire
        int index = qLine.indexOf('#');
        if (index >= 0){
            // on supprime ce qu'il y a apres le #
            qLine = qLine.left(index);
        }

        // test ligne vide
        if (qLine.trimmed().length() == 0){
            continue;
        }

        // analyse d'une variable = valeur
        index = qLine.indexOf('=');
        QString varName = qLine.left(index).trimmed();
        QString varValue = qLine.right(qLine.size() - index - 1).trimmed();

        if (varName.compare("homeDir") == 0){
            this->homeDir = varValue;
        } else  if (varName.compare("connexionFile") == 0){
            this->cnxFileName = varValue;
        } else  if (varName.compare("terminal") == 0){
            this->terminalApp = varValue;
            listTerminalApp.append(varValue);
        } else  if (varName.compare("defaultTerminal") == 0){
            this->defaultTerminalApp = varValue.toInt();
        }  else if (varName.compare("optionX11Forwarding") == 0){
            this->optionX11Forwarding = varValue;
        }  else if (varName.compare("shellLocal") == 0){
            this->shellLocal = varValue;
        }  else {
            QString message = tr("erreur de syntaxe dans le fichier de configuration => ") + tr("nom de variable inconnu : ") + varName;
            QMessageBox::information(NULL,tr("ERREUR"), message);
            qDebug() << "erreur dans le fichier de configuration";
            qDebug() << "nom de variable inconnu : " << varName;
        }
    }
    //qDebug() << "Config::analyseConfigFile : fin";
}

//--------------------------------------------
//
//      Config::abandon
//
//--------------------------------------------
void Config::abandonConfig(){
    qDebug() << "Config::abandon : debut";

    QString message;
    QMessageBox messageBox = QMessageBox(this);
    if (datasModified){
        qDebug() << "Configuration non sauv??e";
        message = "Attention les donn??es de configuration n'ont pas ??t?? sauvegard??es \n";
        messageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save);

        messageBox.setWindowTitle("Configuration non sauv??e");

        messageBox.setInformativeText(message);
        int status = messageBox.exec();
        switch(status){
        case QMessageBox::Cancel:
            return;
            break;
        case QMessageBox::Save:
            saveEditedValuesConfig();
            break;
        }

    }
    editWidget->close();
    qDebug() << "Config::abandon : fin";
}

//--------------------------------------------
//
//      Config::abandonAddApp
//
//--------------------------------------------
void Config::abandonAddApp(){
    qDebug() << "Config::abandonAddApp : debut";

    addAppWidget->close();
    qDebug() << "Config::abandonAddApp : fin";
}

//--------------------------------------------
//
//      Config::ajouterAppterminal
//
//--------------------------------------------
void Config::ajouterAppterminal(){
    qDebug() << "Config::ajouterAppterminal : debut";

    QString tmp = newAppName->text();
    if (!tmp.isEmpty())
        listTerminalAppLabel->addItem(tmp);
    addAppWidget->close();
    datasModified=true;
    qDebug() << "Config::ajouterAppterminal : fin";
}

//--------------------------------------------
//
//      Config::saveEditedValues
//
//--------------------------------------------
void Config::saveEditedValuesConfig(){
    qDebug() << "Config::saveEditedValues : debut";

    editWidget->close();

    cnxFileName = cnxFileNameLabel->text();
    homeDir = homeDirLabel->text();
    terminalApp = terminalAppLabel->text();
    optionX11Forwarding = X11ForwardingLabel->text();
    shellLocal = shellLocalLabel->text();


    QString fileNameWithPath = configFileName;
    //QString fileNameWithPath = homeDir + "/" + configFileName;
    QFile file = QFile(fileNameWithPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QString message = tr("impossible d'ouvrir le fichier de configuration ") + fileNameWithPath;
        QMessageBox::information(NULL,"ERREUR", message);
        qDebug() << "impossible d'ouvrir le fichier de configuration " << fileNameWithPath;
        return;
    }
    QString tmp;

    tmp = "# fichier de configuration multiterm\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    tmp = "# home dir des fichiers de config l'application\n";
    file.write(tmp.toStdString().c_str());
    tmp = "homeDir = " + homeDir + "\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    tmp = "# nom du fichier de description des connexions\n";
    file.write(tmp.toStdString().c_str());
    tmp = "connexionFile = " + cnxFileName + "\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    tmp = "# option de forwarding X11\n";
    file.write(tmp.toStdString().c_str());
    tmp = "optionX11Forwarding = " + optionX11Forwarding + "\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    tmp = "shellLocal = " + shellLocal + "\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    tmp = "# liste des applications terminal disponibles\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    int idx = 0;
    while (!listTerminalApp.value(idx).isEmpty()){
        tmp = "terminal = " + listTerminalApp[idx];
        qDebug() << "ajout de la ligne : " << tmp;
        file.write(tmp.toStdString().c_str());
        file.write("\n");
        idx++;
    }
    tmp = "defaultTerminal = " + QString::number(defaultTerminalApp) + "\n";
    file.write(tmp.toStdString().c_str());
    qDebug() << "ajout de la ligne : " << tmp;
    file.write("\n");

    file.close();
    datasModified=false;

    qDebug() << "Config::saveEditedValues : fin";
}

//--------------------------------------------
//
//      Config::onListeAppTerminalActivated
//
//--------------------------------------------
void Config::onListeAppTerminalActivated(int index)
{
    qDebug() << "Config::onListeAppTerminalActivated => debut";
    terminalApp= listTerminalApp.value(index);
    terminalAppLabel->setText(terminalApp);
    defaultTerminalApp = index;
    qDebug() << "nouvel index = " << QString::number(defaultTerminalApp);
    datasModified=true;
    qDebug() << "Config::onListeAppTerminalActivated => fin";
}

//--------------------------------------------
//
//      Config::ajoutAppTerminal
//
//--------------------------------------------
void Config::ajoutAppTerminal()
{
    addAppWidget = new QWidget();
    addAppWidget->setWindowTitle("Ajout application terminal");

    newAppName = new QLineEdit();
    const char *message = "Saisissez ci-dessous le nom de l'application terminal que vous souhaitez ajouter a la liste des applications disponibles ; \nATTENTION\n : il faut preciser le chemin d'acces si necessaire";
    QFormLayout *layoutAddApp = new QFormLayout;
    layoutAddApp->addRow(new QLabel(tr(message)));
    layoutAddApp->addRow(new QLabel(tr("Application :")), newAppName);

    QHBoxLayout *layoutBouttons = new QHBoxLayout;
    QPushButton *boutonAjouter = new QPushButton("Ajouter");
    layoutBouttons->addWidget(boutonAjouter);
    connect(boutonAjouter, SIGNAL(clicked()), this, SLOT(ajouterAppterminal()));
    QPushButton *boutonAbandon = new QPushButton("Abandon");
    layoutBouttons->addWidget(boutonAbandon);
    connect(boutonAbandon, SIGNAL(clicked()), this, SLOT(abandonAddApp()));
    layoutAddApp->addRow(layoutBouttons);

    datasModified=true;
    editWidget->setLayout(layoutAddApp);
    editWidget->show();
}

//--------------------------------------------
//
//      Config::editValueChanged
//
//--------------------------------------------
void Config::editValueChanged(){
    qDebug() << "Config::editValueChanged => debut";
    datasModified=true;
    qDebug() << "Config::editValueChanged => fin";
}

//--------------------------------------------
//
//      Config::editConfig
//
//--------------------------------------------
void Config::editConfig(){
    qDebug() << "Config::editConfig => debut";

    editWidget = new QWidget();
    editWidget->setWindowTitle("Configuration");
    const char *message = "edition des parametres de configuration";


    homeDirLabel = new QLineEdit();
    homeDirLabel->setText(homeDir);

    cnxFileNameLabel = new QLineEdit();
    cnxFileNameLabel->setText(cnxFileName);
    connect(cnxFileNameLabel,SIGNAL(editingFinished()), this, SLOT(editValueChanged()));

    terminalAppLabel = new QLabel();
    terminalAppLabel->setText(terminalApp);

    X11ForwardingLabel = new QLineEdit();
    X11ForwardingLabel->setText(optionX11Forwarding);

    shellLocalLabel = new QLineEdit();
    shellLocalLabel->setText(shellLocal);

    listTerminalAppLabel = new QComboBox();
    listTerminalAppLabel->setEditable(true);
    qDebug() << "taille de la liste des terminaux " << listTerminalApp.size() ;
    for (int idx = 0 ; idx < listTerminalApp.size() ; idx++){
        qDebug() << "ajout " << listTerminalApp.value(idx);
        listTerminalAppLabel->addItem(listTerminalApp.value(idx));
    }
    qDebug() << "on set la valeur par defaut";
    listTerminalAppLabel->setCurrentIndex(defaultTerminalApp);
    connect(listTerminalAppLabel, SIGNAL(activated(int)), this, SLOT(onListeAppTerminalActivated(int)));

    QPushButton *boutonAjoutApp = new QPushButton("Ajouter app");
    connect(boutonAjoutApp, SIGNAL(clicked()), this, SLOT(ajoutAppTerminal()));
    qDebug() << "on remplit le layout";
    QFormLayout *layoutConfig = new QFormLayout;
    layoutConfig->addRow(new QLabel(tr(message)));
    layoutConfig->addRow(new QLabel(tr("Home Dir                        :")), homeDirLabel);
    layoutConfig->addRow(new QLabel(tr("fichier de connexions           :")), cnxFileNameLabel);
    layoutConfig->addRow(new QLabel(tr("option X11Forwarding            :")), X11ForwardingLabel);
    layoutConfig->addRow(new QLabel(tr("shell local                     :")), shellLocalLabel);
    layoutConfig->addRow(new QLabel(tr("Applications Terminal           :")), listTerminalAppLabel);

    QHBoxLayout *layoutBouttons = new QHBoxLayout;
    QPushButton *boutonSauver = new QPushButton("Sauver");
    layoutBouttons->addWidget(boutonSauver);
    connect(boutonSauver, SIGNAL(clicked()), this, SLOT(saveEditedValuesConfig()));
    QPushButton *boutonAbandon = new QPushButton("Abandon");
    layoutBouttons->addWidget(boutonAbandon);
    connect(boutonAbandon, SIGNAL(clicked()), this, SLOT(abandonConfig()));
    layoutConfig->addRow(layoutBouttons);

    editWidget->setLayout(layoutConfig);
    editWidget->show();
    qDebug() << "Config::editConfig => fin";
}
