#include "comboboxdelegate.h"
#include <QStyledItemDelegate>
#include <QDebug>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


comboBoxDelegate::comboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    //qDebug() << "gjg";
}

QWidget *comboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex&) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(true);

    QSqlQuery query;
    query.exec("SELECT unit_name from units_catalog");
    while (query.next()) {
        QString text = query.value(0).toString();
        editor->addItem(text);
    }

    return editor;
}

void comboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QComboBox *edit = qobject_cast<QComboBox*>(editor);

    if(edit->findText(edit->currentText()) == -1)
    {
         QMessageBox msgBox;
         msgBox.setText("Отсутствует значение");
         msgBox.setIcon(QMessageBox::Question);
         msgBox.setInformativeText("Значение отсутствует в справочнике. Хотите занести его?");
         msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
         msgBox.setDefaultButton(QMessageBox::Yes);
         int ret = msgBox.exec();
         if(ret == 16384)
         {
             QString unit_name = edit->currentText();
             QModelIndex ind = model->index(index.row(), 0);
             QString work_id = model->itemData(ind).first().toString();
             insertToCatalog(unit_name, work_id);

         }

    }

    model->setData(index, edit->currentText());

}

void comboBoxDelegate::insertToCatalog(QString unit_name , QString work_id) const
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec("INSERT INTO units_catalog values (unit_seq.NEXTVAL, '" + unit_name + "')");
    query.exec("UPDATE work_catalog set units_catalog_unit_id = unit_seq.CURRVAL where work_id = "
               + work_id);
    QSqlDatabase::database().commit();
    qDebug() << query.lastError().text();

}
