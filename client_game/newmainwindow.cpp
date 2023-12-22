#include "newmainwindow.h"
#include "ui_newmainwindow.h"
#include <QDebug>
#include <QMessageBox>


NewMainWindow::NewMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMainWindow)
{
    ui->setupUi(this);
   // Question q = client->questions[0];

}

NewMainWindow::~NewMainWindow()
{
    delete ui;
}


//void NewMainWindow::setQuestionView(Question question){
//   // ui->label->setText(QString("Question ") + (question.id + 1));
//}


//void NewMainWindow::on_pushButton2_clicked()
//{
//    if(client->currentQuestion >= client->questions.size()){
//        QMessageBox::information(this, "Notification", "Finish Game!");
//        return;
//    }
//    Question q = client->questions[client->currentQuestion];
//    setQuestionView(q);
//}
