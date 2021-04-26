#include <QAbstractItemModel>
#include <QDebug>

#include "connexionitem.h"

//--------------------------------------------
//
//      ConnexionItem::ConnexionItem
//
//--------------------------------------------
ConnexionItem::ConnexionItem(QWidget *parent) : QAbstractItemModel(){
    qDebug() << "ConnexionItem => constructeur debut";

    qDebug() << "ConnexionItem => constructeur fin";
}



Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) {
    return parent;
}

Q_INVOKABLE QModelIndex parent(const QModelIndex &child){
    return child;
}
Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) {
    return 0;
}
Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) {
    return 0;
}
Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) {
    QVariant localData = QVariant();
    return localData;
}
