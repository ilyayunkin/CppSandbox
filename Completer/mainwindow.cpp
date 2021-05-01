#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGlobal>
#include <QCompleter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Омск, 1 Амурская", 1);
    ui->comboBox->addItem("Омск, 16 Амурская", 2);
    ui->comboBox->addItem("Омск, 21 Амурская", 3);
    ui->comboBox->addItem("Омск, 5 Амурская", 45);
    ui->comboBox->addItem("Сады Дружок, 1 аллея", 4);
    ui->comboBox->addItem("Сады Дружок, 4 аллея", 5);
    QCompleter *completer = new QCompleter({"Омск, 1 Амурская","Омск, 16 Амурская", "Омск, 21 Амурская","Сады Дружок, 1 аллея", "Сады Дружок, 4 аллея"},
                                           this);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comboBox->setCompleter(completer);

//    connect(ui->comboBox, &QComboBox::currentTextChanged,
//            [&](const QString s){
//        qDebug() << "currentTextChanged" << s;
//    });
    connect(ui->comboBox, &QComboBox::textActivated,
            [&](const QString s){
        qDebug() << "currentTextChanged" << s;
    });
    connect(ui->comboBox, QOverload<const int>::of(&QComboBox::activated),
            [&](const int i){
        qDebug() << "activated" << i;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

