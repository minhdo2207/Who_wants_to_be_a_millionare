#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include "client.h"
#include "dialog.h"
#include "historyscore.h"
#include "pvpdialog.h"

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private:
    Ui::Home *ui;
public:
    void setUpUserData();
public:
    Client* client;
private slots:
    void on_pushButton_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // HOME_H
