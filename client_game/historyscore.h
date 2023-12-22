#ifndef HISTORYSCORE_H
#define HISTORYSCORE_H

#include <QDialog>
#include "client.h"

namespace Ui {
class HistoryScore;
}

class HistoryScore : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryScore(QWidget *parent = nullptr);
    ~HistoryScore();

public:
    void setUpHistory();
public:
    Client* client = NULL;
private slots:
    void on_pushButton_clicked();

private:
    Ui::HistoryScore *ui;
};

#endif // HISTORYSCORE_H
