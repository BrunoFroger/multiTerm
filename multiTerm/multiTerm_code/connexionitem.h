#ifndef CONNEXIONITEM_H
#define CONNEXIONITEM_H

#include <QAbstractItemModel>

class ConnexionItem : public  QAbstractItemModel
{
public:
    ConnexionItem(QWidget *parent);

private:
    Q_INVOKABLE virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const = 0;
    Q_INVOKABLE virtual QModelIndex index() const = 0;
    Q_INVOKABLE virtual QModelIndex parent(const QModelIndex &child) const = 0;
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const = 0;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;
};

#endif // CONNEXIONITEM_H
