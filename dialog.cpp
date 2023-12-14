#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}



Dialog::~Dialog()
{
    delete ui;
}



void Dialog::setQuestionView(Question question){
    ui->label_3->setText(this->mode);
    ui->label->setText(QString("Question ") + QString::number(question.id + 1));
    ui->label_2->setText(question.question);
    ui->checkBox->setText(question.answers[0]);
    ui->checkBox_2->setText(question.answers[1]);
    ui->checkBox_3->setText(question.answers[2]);
    ui->checkBox_4->setText(question.answers[3]);

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);

}

void Dialog::setUpFirstQuestion(){
    if(client != NULL && (client->questions).size() > 0){
        Question q = (client->questions).at(0);
        setQuestionView(q);
    }
}

void Dialog::on_pushButton_clicked()
{
    QString mode = this->mode;
    if((client != NULL && (client->questions).size() > 0)){
        bool isWrong = false;
        Question q1 = client->questions[client->currentQuestion];
        qDebug() << "Checked: " << ui->checkBox->isChecked();
        if(ui->checkBox->isChecked() && q1.correctAnswer != 1) isWrong = true;
        if(ui->checkBox_2->isChecked() && q1.correctAnswer != 2) isWrong = true;
        if(ui->checkBox_3->isChecked() && q1.correctAnswer != 3) isWrong = true;
        if(ui->checkBox_4->isChecked() && q1.correctAnswer != 4) isWrong = true;

        if(!isWrong && client->currentQuestion == client->questions.size() - 1) client->currentQuestion++;
        if(isWrong || client->currentQuestion >= client->questions.size() - 1){
            QString result = QString::number(client->currentQuestion) + "/" + QString::number(client->questions.size());
            QMessageBox::information(this, "Notification", "Finished! Your result is " + result);
            client->send(client->user, "END_GAME", result + "|" + mode);
            if(mode == "PRACTICE"){
                hide();
                Home* d = new Home(this);
                d->client = this->client;
                d->show();
                return;
            } else {
                QString result = client->receive();
                result = result.split("&")[1];
                if(result.contains("LOSE")) {
                     client->updateScore(-1);
                } else if(result.contains("WIN")){
                    client->updateScore(1);
                }
                QMessageBox::information(this, "Kết quả", result);
                hide();
                Home* d = new Home(this);
                d->client = this->client;
                d->setUpUserData();
                d->show();
                return;
            }
        }
        client->currentQuestion++;
        Question q = (client->questions).at(client->currentQuestion);
        setQuestionView(q);
    }
}
