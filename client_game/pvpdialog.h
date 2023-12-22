#ifndef PVPDIALOG_H
#define PVPDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class PvpDialog;
}

class PvpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PvpDialog(QWidget *parent = nullptr);
    ~PvpDialog();
public:
    void openPvpQuestionDialog(QString userPvP);
public:
    Client* client;
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PvpDialog *ui;
};

#endif // PVPDIALOG_H
