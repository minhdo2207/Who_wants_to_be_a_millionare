#include "historyscore.h"
#include "ui_historyscore.h"
#include "home.h"

HistoryScore::HistoryScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryScore)
{
    ui->setupUi(this);
}

HistoryScore::~HistoryScore()
{
    delete ui;
}

void HistoryScore::setUpHistory(){
    QVector<History> histories = this->client->getHistoryScore();
    for(History h: histories){
        QString view = h.date + "\t\t" + h.user + "\t" + h.score + "\t" + h.event;
        ui->listWidget->addItem(view);
    }
}


void HistoryScore::on_pushButton_clicked()
{
    hide();
    Home* d = new Home(this);
    d->client = this->client;
    d->show();
}
