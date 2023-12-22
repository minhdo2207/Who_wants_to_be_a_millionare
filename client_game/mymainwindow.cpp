#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QDebug>
#include <QMessageBox>


MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}


void MyMainWindow::on_startGameMode1_clicked()
{
//    hide();
//    Dialog* d = new Dialog(this);
//    d->client = this->client;
//    d->show();
//    d->setUpFirstQuestion();

     QString username = ui->textEdit->toPlainText();
     QString password = ui->textEdit_2->toPlainText();
     User u; u.username = username; u.password = password;
     bool response = client->login_(u);
     if(response){
         QMessageBox::information(this, "Notification", "Login Success!");
         hide();
         Home* d = new Home(this);
         d->client = this->client;
         d->client->user = u.username;
         d->setUpUserData();
         d->show();
     } else {
         QMessageBox::information(this, "Notification", "Wrong username or password!");
     }
}

void MyMainWindow::on_pushButton_clicked()
{
        hide();
        Register* d = new Register(this);
        d->client = this->client;
        d->show();
}
