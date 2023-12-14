#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_pushButton_clicked()
{
        int mode = 1;
        // if(ui->radioButton_2->isChecked()){
        //     mode = 2;
        // }
        hide();
        Dialog* d = new Dialog(this);
        d->client = this->client;
        d->client->PlayGame(mode);
        d->show();
        d->setUpFirstQuestion();
}

void Home::setUpUserData(){
    ui->label_2->setText("Score: " + client->_user.score);
    ui->label_3->setText("Rank: " + client->_user.rank);
}
void Home::on_radioButton_clicked()
{
//    if(ui->radioButton->isChecked()){
//        ui->radioButton_2->setCheckable(false);
//    }else {
//        ui->radioButton_2->setCheckable(true);

//    }
}

void Home::on_radioButton_2_clicked()
{
//    if(ui->radioButton_2->isChecked()){
//        ui->radioButton->setCheckable(false);
//    } else {
//        ui->radioButton->setCheckable(true);

//    }
}

void Home::on_pushButton_3_clicked()
{
    hide();
    HistoryScore* d = new HistoryScore(this);
    d->client = this->client;
    d->show();
    d->setUpHistory();
}

void Home::on_pushButton_2_clicked()
{
    // hide();
    // PvpDialog* d = new PvpDialog(this);
    // d->client = this->client;
    // d->show();
}
