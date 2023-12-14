#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "client.h"
#include "Question.h"
#include "home.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public:
    void setQuestionView(Question question);
    void setUpFirstQuestion();

public:
    Client* client = NULL;
    QString mode = "PRACTICE";
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
