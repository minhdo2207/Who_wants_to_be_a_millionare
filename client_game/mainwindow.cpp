#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(client->questions.size() > 0){
        Question q = client->questions[0];
        setQuestionView(q);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setQuestionView(Question question){
  //  ui->label->setText(QString("Question ") + (question.id + 1));
}


//void MainWindow::on_pushButton2_clicked()
//{
//    if(client->currentQuestion >= client->questions.size()){
//        QMessageBox::information(this, "Notification", "Finish Game!");
//        return;
//    }
//    Question q = client->questions[client->currentQuestion];
//    setQuestionView(q);
//}
