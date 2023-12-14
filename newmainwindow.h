#ifndef NEWMAINWINDOW_H
#define NEWMAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "Question.h"

namespace Ui {
class NewMainWindow;
}

class NewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMainWindow(QWidget *parent = nullptr);
    ~NewMainWindow();

private:
    Ui::NewMainWindow *ui;

public:
    Client* client;
};

#endif // NEWMAINWINDOW_H
