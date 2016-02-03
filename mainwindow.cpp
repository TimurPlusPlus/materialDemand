#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QToolBar>
#include "comboboxdelegate.h"
#include <QAbstractItemDelegate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("TIMBASE");
    db.setUserName("SYSTEM");
    db.setPassword("111111");
    if (!db.open()) {
        QMessageBox::about(this, "ERROR", db.lastError().text());
    }

    QSqlTableModel *model = new QSqlTableModel(0, db);
    ui->tableView->setModel(model);

    QPixmap *pix = new QPixmap("C:\\Users\\1\\Desktop\\1.png");

    ui->pushButton->setIcon(*pix);
    ui->pushButton->setIconSize(QSize(70, 70));
    ui->pushButton->setFixedSize(ui->pushButton->iconSize());
    ui->pushButton->setFlat(true);

    QPixmap *pix2 = new QPixmap("C:\\Users\\1\\Desktop\\2.png");

    ui->pushButton_2->setIcon(*pix2);
    ui->pushButton_2->setIconSize(QSize(70, 70));
    ui->pushButton_2->setFixedSize(ui->pushButton_2->iconSize());
    ui->pushButton_2->setFlat(true);

    QPixmap *pix3 = new QPixmap("C:\\Users\\1\\Desktop\\3.png");

    ui->pushButton_3->setIcon(*pix3);
    ui->pushButton_3->setIconSize(QSize(70, 70));
    ui->pushButton_3->setFixedSize(ui->pushButton_3->iconSize());
    ui->pushButton_3->setFlat(true);

    ui->dockWidget->setFixedWidth(160);

    QPushButton *button  = new QPushButton();
    QPixmap *pix4 = new QPixmap("C:\\Users\\1\\Desktop\\4.png");
    button->setIcon(*pix4);
    button->setIconSize(QSize(50, 50));
    button->setFixedSize(button->iconSize());
    button->setFlat(true);

    QPushButton *button2  = new QPushButton();
    QPixmap *pix5 = new QPixmap("C:\\Users\\1\\Desktop\\5.png");
    button2->setIcon(*pix5);
    button2->setIconSize(QSize(40, 40));
    button2->setFixedSize(button2->iconSize());
    button2->setFlat(true);

    ui->mainToolBar->addWidget(button);
    ui->mainToolBar->addWidget(button2);
    connect(button, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(button2, SIGNAL(clicked()), this, SLOT(delButtonClicked()));

    ui->tableView->setItemDelegateForColumn(2, new comboBoxDelegate);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlTableModel *model2 = (QSqlTableModel*) ui->tableView->model();
    model2->setEditStrategy(QSqlTableModel::OnFieldChange);
    model2->setTable("material_demand3");
    model2->select();
    ui->tableView->setColumnHidden(0, true);



  /*  QSqlQuery query;
    QSqlRecord record;

    query.exec("SELECT * from material_demand2");
    int i = 0;
    QTextCodec* defaultTextCodec = QTextCodec::codecForName("Windows-1251");
    while (query.next()) {
           QByteArray text = query.value(1).toByteArray();
           QString unicode = defaultTextCodec->toUnicode(text);
           record.setValue(1, unicode);
           model2->insertRecord(i, record);
                   i++;
       }*/

}

void MainWindow::addButtonClicked()
{
    QSqlTableModel *model2 = (QSqlTableModel*) ui->tableView->model();
    model2->insertRow(model2->rowCount());
}

void MainWindow::delButtonClicked()
{
    QSqlTableModel *model2 = (QSqlTableModel*) ui->tableView->model();
    model2->removeRow(model2->rowCount() - 1);
}
