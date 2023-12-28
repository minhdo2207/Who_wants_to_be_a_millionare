#include "pvpdialog.h"
#include "ui_pvpdialog.h"
#include "home.h"
#include<QMessageBox>

PvpDialog::PvpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PvpDialog)
{
    ui->setupUi(this);
}

PvpDialog::~PvpDialog()
{
    delete ui;
}

void PvpDialog::on_pushButton_3_clicked()
{
    hide();
    Home* d = new Home(this);
    d->client = this->client;
    d->setUpUserData();
    d->show();
}

void PvpDialog::openPvpQuestionDialog(QString userPvP){
    int mode = 1;
    hide();
    Dialog* d = new Dialog(this);
    d->client = this->client;
    d->mode = "PvP with " + userPvP;
    d->client->PlayGame(mode);
    d->show();
    d->setUpFirstQuestion();
}

void PvpDialog::on_pushButton_clicked()
{
    if(client->isReady == false){
        client->send(client->user, "WAIT_REQUEST", "");
        client->isReady = true;
        ui->label_2->setText("Status: Waiting for PvP Request...");
        ui->pushButton->setText("Disable waiting request");
        QMessageBox::information(this, "Notification",
                                 "Bạn đã bật chế độ chờ PvP.\nHãy chờ yêu cầu thách đấu trong ít phút tới...");

    } else {
        client->send(client->user, "DISABLE_WAIT_REQUEST", "");
        client->isReady = false;
        ui->label_2->setText("Status: Not Ready");
        ui->pushButton->setText("Wait For PvP");
    }

    if(client->isReady){
        QString request = client->waitForPvPRequest();
        if(request.startsWith("PVP_REQUEST")){
            QString domain = request.split("&")[1];
            QString acceptUser = domain.split("\r")[0];
            qDebug() << "User Request: " << acceptUser;
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirm", "Are you accept PvP Request?",
                                   QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                qDebug() << "Accepted!";

                client->send(client->user, "ACCEPT_PVP_REQUEST", acceptUser);
                openPvpQuestionDialog(acceptUser);

            } else {
                qDebug() << "Confuse!";
                client->send(client->user, "CONFUSE_PVP_REQUEST", acceptUser);

            }
        }
    }
}



void PvpDialog::on_pushButton_2_clicked()
{
    QString pvpUser = ui->textEdit->toPlainText();
    client->send(client->user, "SENT_PVP_REQUEST", pvpUser);
    QString response = client->receive();
    if(response.startsWith("SENT_PVP_REQUEST_fail")){
        QMessageBox::information(this, "Notification", pvpUser + " is not online for PvP Request");
    } else if(response.startsWith("SENT_PVP_REQUEST_ok")){
        QString response = client->receive();
        if(response.startsWith("ACCEPT_PVP_REQUEST")){
            openPvpQuestionDialog(pvpUser);
        } else {
            QMessageBox::information(this, "Notification",
                                     pvpUser + " deny your PvP request!");
        }
    } else if(response.startsWith("SENT_PVP_REQUEST_not_rank")){
        QMessageBox::information(this, "Notification",
                                 pvpUser + " greater than 2 ranking!");
    } else {
        QMessageBox::information(this, "Notification", "FAIL: unknow!");
    }
}
