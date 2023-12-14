#include "history_score.h"
#include "ui_history_score.h"

history_score::history_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history_score)
{
    ui->setupUi(this);
}

history_score::~history_score()
{
    delete ui;
}
