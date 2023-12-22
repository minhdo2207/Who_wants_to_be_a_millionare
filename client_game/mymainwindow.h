#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "Question.h"
#include "dialog.h"
#include "register.h"
#include "home.h"

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

private:
    Ui::MyMainWindow *ui;
public:
    Client* client = NULL;
private slots:
    void on_startGameMode1_clicked();
    void on_pushButton_clicked();
};

#endif // MYMAINWINDOW_H
