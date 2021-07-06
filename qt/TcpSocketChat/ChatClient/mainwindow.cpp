#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->messageLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::on_sendButtonButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButtonButton_clicked()
{
    emit newMessage(ui->messageLineEdit->text());
    ui->messageLineEdit->clear();
}

void MainWindow::setChat(QString chat)
{
    ui->chatTextEdit->setText(chat);
}

void MainWindow::setUserList(QStringList setUserList)
{
    ui->userListTextEdit->setText(setUserList.join("\r\n"));
}
