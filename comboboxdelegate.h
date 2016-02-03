#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H
#include <QStyledItemDelegate>
#include <QAbstractItemDelegate>


class comboBoxDelegate : public QStyledItemDelegate
{
public:
    comboBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex&) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const;
    void insertToCatalog(QString, QString) const;

signals:

public slots:
};

#endif // COMBOBOXDELEGATE_H
