#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include "mymainwindow.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    User u;
    QString username = ui->textEdit->toPlainText();
    QString p1 = ui->textEdit_2->toPlainText();
    QString p2 = ui->textEdit_3->toPlainText();

    if(p1 != p2){
        QMessageBox::information(this, "Notification", "Hay nhap dung password");
        return;
    }

    u.username = username;
    u.password = p1;
    u.score = "0";
    u.rank = "Bronze";
    client->register_(u);

    QString response = client->receive();
    if(response.startsWith("REGISTER_SUCCESS")){
        QMessageBox::information(this, "Notification", "Register Success!");
        hide();
        MyMainWindow* d = new MyMainWindow(this);
        d->client = this->client;
        d->client->_user = u;
        d->show();
    } else {
        QMessageBox::information(this, "Notification", "Fail");
    }
}
