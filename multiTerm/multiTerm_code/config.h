#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QString;
class QFile;
class QLabel;
class QComboBox;
QT_END_NAMESPACE

class Config : public QDialog
{
    Q_OBJECT

public:
    //Config();
    Config(QString homeDir, QString configFileName);
    QString getHomeDir();
    QString getCnxFileName();
    QString getTerminalAppName();
    QString getOptionX11Forwarding();
    void editConfig();

private slots:
    void abandonConfig();
    void saveEditedValuesConfig();
    void onListeAppTerminalActivated(int index);
    void ajoutAppTerminal();
    void ajouterAppterminal();
    void abandonAddApp();
    void changeDefaultApp();

private :
    QString configFileName;

    // données du fichier de configuration
    QString homeDir;
    QString cnxFileName;
    QString terminalApp;
    QStringList listTerminalApp;
    QString optionX11Forwarding;
    int defaultTerminalApp;

    // données d'affichage
    QWidget *editWidget;
    QWidget *addAppWidget;
    QLineEdit *homeDirLabel;
    QLineEdit *cnxFileNameLabel;
    QLabel *terminalAppLabel;
    QComboBox *listTerminalAppLabel;
    QLineEdit *newAppName;
    QLineEdit *X11ForwardingLabel;

    void analyseConfigFile();
};

#endif // CONFIG_H
